/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:09:30 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:54:43 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_data	make_data(t_arguments args)
{
	t_data	data;

	data.args = args;
	data.sync = make_mutex(1ul);
	data.forks = make_mutex(args.count);
	data.people = make_people(args.count);
	data.stop = false;
	data.ok = (data.sync && data.forks && data.people);
	return (data);
}

void	delete_data(t_data data)
{
	delete_people(data.people);
	delete_mutex(data.sync, 1ul);
	delete_mutex(data.forks, data.args.count);
}

void	prepare_data(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->args.count)
	{
		data->people[i].data = data;
		make_thread(&data->people[i]);
		i++;
	}
}

void	await_data(t_data data)
{
	long	i;

	i = 0;
	while (i < data.args.count)
		pthread_join(data.people[i++].thread, NULL);
}
