/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:07 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 18:27:06 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_parameters
{
	long	population;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	cycle_max;
	bool	failure;
}	t_parameters;

typedef struct s_stage t_stage;

typedef struct s_person
{
	long		id;
	long		last_eat;
	t_mutex		fork;
	t_thread	handle;
	t_stage		*stage;
}	t_person;

typedef struct s_stage
{
	t_mutex			sync;
	t_mutex			start;
	t_person		*people;
	t_parameters	params;
	bool			failure;
}	t_stage;

long	time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((long)tv.tv_sec * 1000l + (long)tv.tv_usec / 1000l);
}

void	*new(unsigned long unit, unsigned long count)
{
	void	*allocation;

	if (SIZE_MAX / count < unit)
		return (NULL);
	allocation = malloc(unit * count);
	if (allocation)
		bzero(allocation, unit * count);
	return (allocation);
}

t_mutex	make_mutex(bool *failure)
{
	t_mutex	mutex;

	if (pthread_mutex_init(&mutex, NULL) != 0)
		*failure = true;
	return (mutex);
}

void	delete_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
	bzero(mutex, sizeof(t_mutex));
}

void	lock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
}

void	unlock_mutex(t_mutex *mutex)
{
	pthread_mutex_unlock(mutex);
}

void	join_thread(t_thread thread)
{
	pthread_join(thread, NULL);
}

long	parse_parameter(char **args, int i, t_parameters *params)
{
	long	n;

	if (params->failure)
		n = -1;
	else
		n = atol(args[i]);
	if (n < 0 || n > INT_MAX)
		params->failure = true;
	if (params->failure)
		return (-1);
	return (n);
}

t_parameters	make_parameters(int argc, char **argv)
{
	t_parameters	params;

	bzero(&params, sizeof(t_parameters)); // TODO(XENOBAS): polyfill
	if (argc != 4 && argc != 5)
		params.failure = true;
	params.population = parse_parameter(argv, 0, &params);
	params.time_die = parse_parameter(argv, 1, &params);
	params.time_eat = parse_parameter(argv, 2, &params);
	params.time_sleep = parse_parameter(argv, 3, &params);
	params.cycle_max = -1;
	if (argc == 5)
		params.cycle_max = parse_parameter(argv, 4, &params);
	return (params);
}

void	*person_routine(t_person *person)
{
	unlock_mutex(&person->stage->start);
	lock_mutex(&person->stage->sync);
	printf("%ld is talking\n", person->id);
	unlock_mutex(&person->stage->sync);
	return (NULL);
}

t_thread	make_person_thread(t_person *person)
{
	t_thread	thread;

	bzero(&thread, sizeof(t_thread));
	if (!person->stage->failure)
		if (pthread_create(&thread, NULL, (void *)person_routine, person) != 0)
			person->stage->failure = true;
	return (thread);
}

t_person	*make_people(t_stage *stage)
{
	long		i;
	t_person	*people;

	i = 0;
	people = new(sizeof(t_person), stage->params.population);
	while (people && i < stage->params.population && !stage->failure)
	{
		people[i].stage = stage;
		people[i].id = (i + 1);
		people[i].fork = make_mutex(&stage->failure);
		people[i].handle = make_person_thread(&people[i]);
		people[i].last_eat = time_now();
		i++;
	}
	return (people);
}

t_stage	*make_stage(t_parameters params)
{
	t_stage	*stage;

	stage = new(sizeof(t_stage), 1);
	printf("stage = %p\n", stage);
	if (stage)
	{
		stage->params = params;
		stage->sync = make_mutex(&stage->failure);
		if (stage->failure)
			return (free(stage), NULL);
		stage->start = make_mutex(&stage->failure);
		if (stage->failure)
			return (delete_mutex(&stage->sync), free(stage), NULL);
		lock_mutex(&stage->start);
		stage->people = make_people(stage);
		if (stage->people)
			return (delete_mutex(&stage->start), delete_mutex(&stage->sync), free(stage), NULL);
	}
	return (stage);
}

int	main(int argc, char **argv)
{
	t_stage			*stage;
	t_parameters	params;

	// Parse arguments
		// check arguments length to be in range [4, 5]
		// atol on all arguments with -1 representing failure
	params = make_parameters(argc - 1, &argv[1]);
	// Verify arguments
		// if error stop program
	if (params.failure)
		return (printf("error: incorrect arguments\n"), 1);
	// Create table
		// people is an array of { fork, id, eat_stamp }
		// sync lock dedicated for all actions that are to be visible
		// start lock
	stage = make_stage(params);
	if (!stage || stage->failure)
		return (printf("error: could not create the stage\n"), 1);
	printf("we are starting now\n");
	unlock_mutex(&stage->start);
	for (long i = 0; i < params.population; i++)
		join_thread(stage->people[i].handle);
	// Make people alive
		// wait on start lock (people's perspective)
		// turn on start lock (main thread perspective)
	// Simulate people
		// pick fork if all is alive
		// pick fork if all is alive
		// start eating if all is alive
		// start sleeping if all is alive
		// start thinking if all is alive
		// if someone is dead stop
	// Clean up the table
		// destroy all locks (sync, start, forks)
		// destroy people array
	return (0);
}
