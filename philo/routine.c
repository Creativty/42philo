/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:31:16 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 16:02:10 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	routine_print(t_person *p, t_data *data, const char *msg)
{
	lock_mutex(data->sync);
	if (data->stop == false)
		printf("%lu %ld %s\n", instant_now() - p->instant_start, p->id, msg);
	unlock_mutex(data->sync);
}

bool	routine_is_down(t_person *p, t_data *data)
{
	t_ulong	instant;
	bool	death_by_hunger;
	bool	death;

	lock_mutex(data->sync);
	instant = instant_now();
	death_by_hunger = (instant - p->instant_eat > (t_ulong)data->args.t_die);
	if (!data->stop && death_by_hunger)
		printf("%lu %ld %s\n", instant - p->instant_start, p->id, "has died");
	data->stop = (data->stop || death_by_hunger);
	death = data->stop;
	unlock_mutex(data->sync);
	return (death);
}

void	routine_eat(t_person *p, t_data *data)
{
	if (routine_is_down(p, data))
		return ;
	lock_mutex(&data->forks[(p->id - 1) % data->args.count]);
	routine_print(p, data, "has taken a fork");
	lock_mutex(&data->forks[(p->id + 0) % data->args.count]);
	routine_print(p, data, "has taken a fork");
	routine_print(p, data, "is eating");
	instant_sleep(data->args.t_eat);
	p->instant_eat = instant_now();
	unlock_mutex(&data->forks[(p->id + 0) % data->args.count]);
	unlock_mutex(&data->forks[(p->id - 1) % data->args.count]);
}

void	routine_sleep(t_person *p, t_data *data)
{
	if (routine_is_down(p, data))
		return ;
	routine_print(p, data, "is sleeping");
	instant_sleep(data->args.t_sleep);
}

void	routine_think(t_person *p, t_data *data)
{
	if (routine_is_down(p, data))
		return ;
	routine_print(p, data, "is thinking");
}

void	*routine_thread(t_person *p)
{
	t_data	*data;

	data = p->data;
	p->instant_start = instant_now();
	p->instant_eat = p->instant_start;
	while (!routine_is_down(p, data))
	{
		routine_eat(p, data);
		routine_sleep(p, data);
		routine_think(p, data);
	}
	return (NULL);
}
