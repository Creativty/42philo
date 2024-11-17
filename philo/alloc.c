/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:27:01 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 15:43:24 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	new_zero(char *region, unsigned long size)
{
	unsigned long	i;

	i = 0;
	while (i < size)
		region[i++] = '\0';
	return (i);
}

void	*new(unsigned long unit, unsigned long count)
{
	void	*allocation;

	if (SIZE_MAX / count < unit)
		return (NULL);
	allocation = malloc(unit * count);
	if (allocation)
		new_zero(allocation, unit * count);
	return (allocation);
}
