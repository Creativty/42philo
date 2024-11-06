/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:04:11 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 11:57:28 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

bool	rune_is_digit(const char rune)
{
	return (rune >= '0' && rune <= '9');
}

void	mem_zero(void *mem, size_t size)
{
	size_t	i;

	if (mem)
	{
		i = 0;
		while (i < size)
			((char *)mem)[i++] = '\0';
	}
}

long	time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((long)tv.tv_sec * 1000l + (long)tv.tv_usec / 1000l);
}

long	strconv_long(const char *str)
{
	int		i;
	long	value;

	i = 0;
	value = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (!rune_is_digit(str[i]))
			return (-1);
		value = (value * 10) + (str[i++] - '0');
		if (value > (long)INT_MAX)
			return (-1);
	}
	return (value);
}
