/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:20:37 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 14:05:50 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thread_create(pthread_t *handle, t_thread_fn fn, t_thread_args *args)
{
	void	*(*_fn)(void *);
	
	_fn = (void *)fn;
	return (pthread_create(handle, NULL, _fn, args) == 0);
}

void	thread_sleep(long duration)
{
	long	start;

	if (duration == 0)
		return ;
	start = time_now();
	while (1)
	{
		if (time_now() - start >= duration)
			break ;
	}
}
