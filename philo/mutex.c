/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:31:28 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 15:32:31 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	make_mutex(t_mutex *mutex)
{
	return (pthread_mutex_init(&mutex, NULL) == 0)
}

bool	delete_mutex(t_mutex *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
		return (false);
	bzero(mutex, sizeof(t_mutex));
	return (true);
}

bool	lock_mutex(t_mutex *mutex)
{
	return (pthread_mutex_lock(mutex) == 0);
}

bool	unlock_mutex(t_mutex *mutex)
{
	return (pthread_mutex_unlock(mutex) == 0);
}
