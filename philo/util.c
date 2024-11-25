/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:35:09 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:42:07 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	mem_zero(void *memory, unsigned long size)
{
	unsigned long	i;

	i = 0;
	if (memory == NULL)
		return ;
	while (i < size)
		((char *)memory)[i++] = '\0';
}

long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	thread_sleep(long duration_ms)
{
	long	instant_start;

	instant_start = time_now();
	while (time_now() - instant_start < duration_ms)
		;
}
