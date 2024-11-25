/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:48:46 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:46:29 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	delete_mutex(t_mutex *m, t_ulong count)
{
	t_ulong	i;

	i = 0;
	while (m && i < count)
		pthread_mutex_destroy(&m[i++]);
	free(m);
}

t_mutex		*make_mutex(t_ulong count)
{
	t_ulong	i;
	t_mutex	*m;

	i = 0;
	m = malloc((t_ulong)sizeof(t_mutex) * count);
	while (m && i < count)
	{
		if (pthread_mutex_init(&m[i], NULL) != 0)
			return (delete_mutex(m, i), NULL);
		i++;
	}
	return (m);
}

void	lock_mutex(t_mutex *m)
{
	pthread_mutex_lock(m);
}

void	unlock_mutex(t_mutex *m)
{
	pthread_mutex_unlock(m);
}
