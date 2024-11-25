/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:27 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:39:38 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_ulong	instant_now(void)
{
	int				retval;
	struct timeval	tv;

	retval = gettimeofday(&tv, NULL);
	if (retval == -1)
		return ((t_ulong)LONG_MAX);
	return ((t_ulong)tv.tv_sec * 1000ul + (t_ulong)tv.tv_usec / 1000ul);
}

t_ulong	instant_sleep(t_ulong duration_millis)
{
	t_ulong	instant_start;

	instant_start = instant_now();
	while (instant_now() - instant_start < duration_millis)
		;
	return (instant_now());
}
