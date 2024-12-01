/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:58:37 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 19:08:01 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*mutex_make(t_ulong count)
{
	bool	ok;
	t_ulong	i;
	t_mutex	*m;

	i = 0ul;
	m = (t_mutex *)malloc(sizeof(t_mutex) * count);
	ok = !!m;
	while (i < count && ok)
		ok = (pthread_mutex_init(&m[i], NULL) == 0);
	if (ok)
		return (m);
	return (mutex_delete(m, i), NULL);
}

void	mutex_lock(t_mutex *m)
{
	pthread_mutex_lock(m);
}

void	mutex_unlock(t_mutex *m)
{
	pthread_mutex_unlock(m);
}

void	mutex_delete(t_mutex *m, t_ulong count)
{
	t_ulong	i;

	i = 0;
	while (m && i < count)
		pthread_mutex_destroy(&m[i++]);
	free(m);
}
