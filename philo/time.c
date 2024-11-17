/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:26:31 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 18:03:15 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((long)tv.tv_sec * 1000l + (long)tv.tv_usec / 1000l);
}

void	sleep(long ms)
{
	long	start;

	start = now();
	while (now() - start < ms)
		;
}
