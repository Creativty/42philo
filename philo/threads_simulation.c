/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:16:23 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 10:07:59 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulate_thread(void *_args)
{
	t_thread_args	*args;

	if (_args == NULL)
		return (NULL);
	args = (t_thread_args *)_args;
	pthread_mutex_lock(&args->ctx->printf);
		printf("%ld says wazzap\n", args->id);
		fflush(stdout);
	pthread_mutex_unlock(&args->ctx->printf);
	return (args);
}
