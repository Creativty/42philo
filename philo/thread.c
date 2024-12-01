/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:26:21 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:30:11 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_thread	thread_start(void *(*f)(void *), t_person *p)
{
	t_thread	t;

	pthread_create(&t, NULL, f, p);
	return (t);
}

void	thread_await(t_thread t)
{
	pthread_join(t, NULL);
}
