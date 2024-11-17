/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:27:01 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 16:36:01 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	zero(char *region, unsigned long size)
{
	unsigned long	i;

	i = 0;
	while (i < size)
		region[i++] = '\0';
	return (i);
}

void	*new(unsigned long unit, unsigned long count)
{
	static long	counter = 0;
	void		*allocation;

	if (counter == -1)
		return (NULL);
	if (SIZE_MAX / count < unit)
		return (NULL);
	allocation = malloc(unit * count);
	if (allocation)
	{
		zero(allocation, unit * count);
		counter++;
	}
	return (allocation);
}