/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:42:43 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 19:44:32 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mem_fill(void *mem, t_ulong len, unsigned char byte)
{
	t_ulong	i;

	i = 0;
	while (mem && i < len)
		((unsigned char *)mem)[i++] = byte;
}

void	mem_copy(void *src, void *dst, t_ulong len)
{
	t_ulong	i;

	i = 0;
	while (src && dst && i < len)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
}
