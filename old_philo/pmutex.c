/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pmutex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:05:44 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 14:48:31 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	mutex_create(t_mutex *mutex)
{
	return (pthread_mutex_init(mutex, NULL) == 0);
}

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
}

void	mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(mutex);
}

bool	mutex_set_bool(t_mutex *mutex, bool *identifier, bool value)
{
	mutex_lock(mutex);
	*identifier = value;
	mutex_unlock(mutex);
	return (value);
}

bool	mutex_get_bool(t_mutex *mutex, bool *identifier)
{
	bool	value;

	mutex_lock(mutex);
	value = *identifier;
	return (mutex_unlock(mutex), value);
}
