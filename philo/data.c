/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:42:01 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:29:48 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	try_mutex_make(t_data_result *d, t_mutex **out, t_ulong count)
{
	t_mutex	*m;

	if (d == NULL || out == NULL || d->ok == false)
		return ;
	m = mutex_make(count);
	d->ok = (m != NULL);
	if (d->ok)
		*out = m;
}

static void	try_group_make(t_data_result *d, t_person **out, t_ulong count)
{
	t_person	*g;

	if (d == NULL || out == NULL || d->ok == false)
		return ;
	g = group_make(count);
	d->ok = (g != NULL);
	if (d->ok)
		*out = g;
}

t_data_result	data_make(t_args_result p, bool has_cycles)
{
	t_data_result	d;

	mem_fill(&d, sizeof(t_data_result), '\0');
	mem_copy(&p.count, &d.args, sizeof(t_ulong) * 5);
	d.args.has_cycles = has_cycles;
	d.ok = p.ok;
	try_mutex_make(&d, &d.lock_forks, d.args.count);
	try_mutex_make(&d, &d.lock_sync, 1ul);
	try_group_make(&d, &d.group, d.args.count);
	return (d);
}

void	data_init(t_data_result *d)
{
	t_ulong	i;

	if (d == NULL || d->ok == false)
		return ;
	data_group_init(d);
	i = 0;
	while (d->ok && i < d->args.count)
	{
		mutex_lock(d->group[i].lock_eat);
		d->group[i].time_eat = time_now();
		mutex_unlock(d->group[i].lock_eat);
		d->group[i].t = thread_start(person_routine, &d->group[i]);
		i++;
	}
}

void	data_await(t_data_result *d)
{
	t_ulong	i;

	if (d == NULL || d->ok == false)
		return ;
	i = 0;
	while (i < d->args.count)
		thread_await(d->group[i++].t);
}

void	data_delete(t_data_result *d)
{
	if (!d)
		return ;
	mutex_delete(d->lock_forks, d->args.count);
	mutex_delete(d->lock_sync, 1ul);
	group_delete(d->group, d->args.count);
	d->lock_forks = NULL;
	d->lock_sync = NULL;
}
