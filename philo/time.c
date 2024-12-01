/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:18:24 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:19:18 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

t_ulong	time_now(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((t_ulong)(tv.tv_sec * 1000) + (t_ulong)(tv.tv_usec / 1000));
}
