/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:33:15 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:37:45 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

long	math_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

long	math_abs(long a)
{
	if (-a >= 0)
		return (-a);
	return (a);
}

long	math_parse_long(char *str)
{
	int		i;
	long	x;
	long	sign;

	i = 0;
	x = 0;
	sign = 1;
	if (str)
	{
		while (is_space(str[i]))
			i++;
		while (is_sign(str[i]))
			if (str[i++] == '-')
				sign *= -1;
		while (is_digit(str[i]))
			x = (x * 10) + (long)(str[i++] - '0');
		if (x < (long)INT_MIN || x > (long)INT_MAX || str[i] != '\0')
			return (-1);
	}
	return (sign * x);
}
