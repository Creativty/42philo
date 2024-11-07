/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:12:06 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 13:17:45 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_mutex *lock, long id, const char *msg)
{
	static long	start = -1;
	long		timestamp;

	pthread_mutex_lock(lock);
	timestamp = time_now();
	if (start == -1)
		start = timestamp;
	printf("%ld %ld %s\n", timestamp - start, id, msg);
	pthread_mutex_unlock(lock);
}
