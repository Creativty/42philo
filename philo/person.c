/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:28:20 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:31:34 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*person_routine(void *x)
{
	t_person	*p;

	p = (t_person *)x;
	if (p == NULL)
		return (NULL);
	mutex_lock(p->d->lock_sync);
	printf("%lu says hi\n", p->id);
	mutex_unlock(p->d->lock_sync);
	return (NULL);
}
