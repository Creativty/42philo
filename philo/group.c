/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:07:09 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:25:32 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_person	*group_make(t_ulong	count)
{
	t_ulong		size;
	t_person	*g;

	size = sizeof(t_person) * count;
	g = (t_person *)malloc(size);
	return (mem_fill(g, size, '\0'), g);
}

void	group_delete(t_person *g, t_ulong count)
{
	t_ulong	i;

	i = 0;
	while (i < count && g)
		mutex_delete(g[i++].lock_eat, 1ul);
	mem_fill(g, sizeof(t_person) * count, '\0');
	free(g);
}

void	data_group_init(t_data_result *d)
{
	t_ulong		i;
	t_person	*g;

	if (d == NULL || d->group == NULL || d->ok == false)
		return ;
	i = 0;
	g = d->group;
	while (g && i < d->args.count)
	{
		g[i].d = d;
		g[i].id = (i + 1ul);
		g[i].lock_eat = mutex_make(1ul);
		i++;
	}
}
