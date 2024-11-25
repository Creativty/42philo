/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:02:15 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 11:02:23 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_mutex	*make_mutex(unsigned long count)
{
	unsigned long	i;
	t_mutex			*m;

	i = 0;
	m = malloc(sizeof(t_mutex) * count);
	while (m && i < count)
		pthread_mutex_init(&m[i++], NULL);
	return (m);
}

void	delete_mutexes(t_mutex *m, long count)
{
	long	i;

	i = 0;
	while (m && i < count)
		pthread_mutex_destroy(&m[i++]);
}
