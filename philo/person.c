/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:35:24 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 11:03:03 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_person	*make_people(unsigned long count)
{
	unsigned long	i;
	t_person		*p;

	i = 0;
	p = malloc(sizeof(t_person) * count);
	while (p && i < count)
	{
		p[i].id = i + 1;
		p[i].cycle = 0;
		p[i].last_eat = -1;
		i++;
	}
	return (p);
}

t_mutex	*person_fork(t_person *p, long delta)
{
	return (&p->shared->forks[(p->id + delta) % p->shared->count]);
}

void	person_fork_hold(t_person *p, long delta)
{
	t_mutex	*fork;

	fork = person_fork(p, delta);
	pthread_mutex_lock(fork);
}

void	person_fork_drop(t_person *p, long delta)
{
	t_mutex	*fork;

	fork = person_fork(p, delta);
	pthread_mutex_unlock(fork);
}

bool	person_do_stop(t_person *p, long timestamp)
{
	bool	do_stop;

	pthread_mutex_lock(p->shared->sync);
	do_stop = p->shared->death || (p->last_eat != -1 && time_now() - p->last_eat >= p->shared->time_death);
	if (do_stop && p->shared->death == false)
		print(p, "has died", timestamp);
	p->shared->death = p->shared->death || do_stop;
	pthread_mutex_unlock(p->shared->sync);
	return (do_stop);
}
