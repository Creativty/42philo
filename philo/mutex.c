/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:31:28 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 16:21:20 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_result_mutex	make_mutex(void)
{
	t_mutex	m;

	if (pthread_mutex_init(&m, NULL) != 0)
		return (RESULT_FAIL(mutex, m));
	return (RESULT_OK(mutex, m));
}

void	delete_mutex(t_result_mutex m)
{
	if (!m.ok)
		return ;
	pthread_mutex_destroy(&m.data);
	zero((void *)&m.data, sizeof(t_mutex));
}

void	lock_mutex(t_result_mutex m)
{
	if (m.ok == false)
		return ;
	pthread_mutex_lock(&m.data);
}

void	unlock_mutex(t_result_mutex m)
{
	if (m.ok == false)
		return ;
	pthread_mutex_lock(&m.data);
}
