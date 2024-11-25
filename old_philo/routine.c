/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:35:58 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 14:16:22 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

bool	routine_eat_right(t_person *p)
{
	person_fork_hold(p, +0);
	if (person_do_stop(p, time_now()))
		return (person_fork_drop(p, +0), true);
	print(p, "has picked a right fork", time_now());
	person_fork_hold(p, -1);
	if (person_do_stop(p, time_now()))
		return (person_fork_drop(p, -1), person_fork_drop(p, +0), true);
	print(p, "has picked a left fork", time_now());
	if (person_do_stop(p, time_now()))
		return (person_fork_drop(p, -1), person_fork_drop(p, +0), true);
	print(p, "is eating", time_now());
	p->last_eat = time_now();
	thread_sleep(p->shared->time_eat);
	p->cycle += 1;
	if (p->shared->cycles > -1 && p->shared->cycles <= p->cycle)
		return (person_fork_drop(p, -1), person_fork_drop(p, +0), true);
	return (person_fork_drop(p, -1), person_fork_drop(p, +0),
		person_do_stop(p, time_now()));
}

bool	routine_eat_left(t_person *p)
{
	person_fork_hold(p, -1);
	if (person_do_stop(p, time_now()))
		return (person_fork_drop(p, -1), true);
	print(p, "has picked a left fork", time_now());
	person_fork_hold(p, +0);
	if (person_do_stop(p, time_now()))
		return (person_fork_drop(p, +0), person_fork_drop(p, -1), true);
	print(p, "has picked a right fork", time_now());
	if (person_do_stop(p, time_now()))
		return (person_fork_drop(p, +0), person_fork_drop(p, -1), true);
	print(p, "is eating", time_now());
	p->last_eat = time_now();
	thread_sleep(p->shared->time_eat);
	p->cycle += 1;
	if (p->shared->cycles > -1 && p->shared->cycles <= p->cycle)
		return (person_fork_drop(p, +0), person_fork_drop(p, -1), true);
	return (person_fork_drop(p, +0), person_fork_drop(p, -1),
		person_do_stop(p, time_now()));
}

bool	routine_sleep(t_person *p)
{
	if (!person_do_stop(p, time_now()))
		print(p, "is sleeping", time_now());
	if (!person_do_stop(p, time_now()))
		thread_sleep(p->shared->time_sleep);
	return (person_do_stop(p, time_now()));
}

bool	routine_think(t_person *p)
{
	if (!person_do_stop(p, time_now()))
		print(p, "is thinking", time_now());
	return (person_do_stop(p, time_now()));
}

void	*routine(void *arg)
{
	t_person	*p;
	bool		(*routine_eat)(t_person *);

	p = (t_person *)arg;
	p->last_eat = time_now();
	routine_eat = routine_eat_right;
	if (p->id % 2)
	{
		routine_eat = routine_eat_left;
		thread_sleep(5);
	}
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
