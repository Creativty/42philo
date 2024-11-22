/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:55:42 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/22 17:48:55 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_shared	t_shared;

typedef struct s_person
{
	long		id;
	long		cycle;
	long		last_eat;
	t_thread	thread;
	t_shared	*shared;
}	t_person;

typedef struct s_shared
{
	t_person	*people;
	t_mutex		*print;
	t_mutex		*forks;
	t_mutex		*sync;
	bool		death;
	long		count;
	long		cycles;
	long		instant_start;
	long		time_eat;
	long		time_sleep;
	long		time_death;
}	t_shared;

void	mem_zero(void *memory, unsigned long size)
{
	unsigned long	i;

	i = 0;
	if (memory == NULL)
		return ;
	while (i < size)
		((char *)memory)[i++] = '\0';
}

long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	thread_sleep(long duration_ms)
{
	long	instant_start;

	instant_start = time_now();
	while (1)
		if (time_now() - instant_start >= duration_ms)
			break ;
}

void	print(t_person *p, char *msg)
{
	t_mutex		*lock;

	lock = p->shared->print;
	pthread_mutex_lock(lock);
	printf("%ld %ld %s\n", time_now() - p->shared->instant_start, p->id, msg);
	pthread_mutex_unlock(lock);
}

bool	routine_is_dead(t_person *p)
{
	bool	do_stop;

	pthread_mutex_lock(p->shared->sync);
	do_stop = p->shared->death || (p->last_eat != -1 && time_now() - p->last_eat >= p->shared->time_death);
	if (!p->shared->death && do_stop) {
		p->shared->death = true;
		print(p, "has died");
	}
	pthread_mutex_unlock(p->shared->sync);
	return (do_stop);
}

bool	routine_eat(t_person *p)
{
	if (routine_is_dead(p))
		return (true);
	pthread_mutex_lock(&p->shared->forks[(p->id - 1) % p->shared->count]);
	print(p, "has picked a fork");
	if (routine_is_dead(p))
		return (pthread_mutex_unlock(&p->shared->forks[(p->id - 1) % p->shared->count]), true);
	pthread_mutex_lock(&p->shared->forks[(p->id + 0) % p->shared->count]);
	if (routine_is_dead(p))
		return (pthread_mutex_unlock(&p->shared->forks[(p->id - 1) % p->shared->count]), pthread_mutex_unlock(&p->shared->forks[(p->id + 0) % p->shared->count]), true);
	print(p, "has picked a fork");
	if (!routine_is_dead(p))
	{
		print(p, "is eating");
		thread_sleep(p->shared->time_eat);
		p->last_eat = time_now();
		p->cycle++;
	}
	pthread_mutex_unlock(&p->shared->forks[(p->id + 0) % p->shared->count]);
	pthread_mutex_unlock(&p->shared->forks[(p->id - 1) % p->shared->count]);
	return (routine_is_dead(p));
}

bool	routine_sleep(t_person *p)
{
	if (routine_is_dead(p))
		return (true);
	print(p, "is sleeping");
	thread_sleep(p->shared->time_sleep);
	return (routine_is_dead(p));
}

bool	routine_think(t_person *p)
{
	if (routine_is_dead(p))
		return (true);
	print(p, "is thinking");
	return (routine_is_dead(p));
}

void	*routine(void *arg)
{
	t_person	*p;

	p = (t_person *)arg;
	if (p->id % 2 == 1)
		thread_sleep(p->shared->time_eat / 4);
	while (1)
	{
		if (routine_eat(p))
			return (NULL);
		if (routine_sleep(p))
			return (NULL);
		if (routine_think(p))
			return (NULL);
	}
	return (NULL);
}

int	main(void)
{
	t_shared	s;

	// Allocation
	s.count = 3;
	s.death = false;
	s.cycles = -1;
	s.time_eat = 100;
	s.time_sleep = 100;
	s.time_death = 300;
	{ // Sync lock
		s.sync = malloc(sizeof(t_mutex) * 1);
		if (s.sync == NULL)
			return (fprintf(stderr, "error: malloc `s.sync`\n"), 1);
		pthread_mutex_init(s.sync, NULL);
	}
	{ // Print lock
		s.print = malloc(sizeof(t_mutex) * 1);
		if (s.print == NULL)
			return (fprintf(stderr, "error: malloc `s.print`\n"), 1);
		pthread_mutex_init(s.print, NULL);
	}
	{ // Fork locks
		s.forks = malloc(sizeof(t_mutex) * s.count);
		if (s.forks == NULL)
			return (fprintf(stderr, "error: malloc `s.forks`\n"), 1);
		for (int i = 0; i < s.count; i++)
			pthread_mutex_init(&s.forks[i], NULL);
	}
	{ // People instances
		s.people = malloc(sizeof(t_person) * s.count);
		if (s.people == NULL)
			return (fprintf(stderr, "error: malloc `s.people`\n"), 1);
		for (int i = 0; i < s.count; i++) {
			mem_zero(&s.people[i], sizeof(t_person));

			s.people[i].id = i + 1;
			s.people[i].shared = &s;
			s.people[i].last_eat = -1;
		}
		// People instances threads
		s.instant_start = time_now();
		for (int i = 0; i < s.count; i++)
			pthread_create(&s.people[i].thread, NULL, routine, &s.people[i]);
	}
	for (int i = 0; i < s.count; i++)
		pthread_join(s.people[i].thread, NULL);
	// Deallocation
	for (int i = 0; i < s.count; i++)
		pthread_mutex_destroy(&s.forks[i]);
	pthread_mutex_destroy(s.print);
	pthread_mutex_destroy(s.sync);
	free(s.people);
	free(s.forks);
	free(s.print);
	free(s.sync);
	return (0);
}
