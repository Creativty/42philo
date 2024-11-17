/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:37:00 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 16:41:33 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_forks(t_result_mutex *forks, long count)
{
	long	i;

	i = 0;
	if (forks)
	{
		while (i < count)
			delete_mutex(forks[i++]);
		free(forks);
	}
}

t_result_mutex	*make_forks(long count, void *dependency)
{
	long			i;
	bool			failed;
	t_result_mutex	*forks;

	if (dependency == NULL)
		return (NULL);
	forks = new(sizeof(t_result_mutex), count);
	if (forks)
	{
		i = 0;
		failed = false;
		while (i < count)
		{
			forks[i] = make_mutex();
			failed = failed || !forks[i].ok;
			i++;
		}
		if (failed)
			return (delete_forks(forks, count), NULL);
	}
	return (forks);
}
