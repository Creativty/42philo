/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:59:10 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 13:59:16 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_thread_args	*make_thread_args(t_context *ctx, long id)
{
	t_thread_args	*args;

	args = malloc(sizeof(t_thread_args));
	if (args)
	{
		args->id = id;
		args->ctx = ctx;
	}
	return (args);
}

t_thread	make_thread(t_context *ctx, long id)
{
	t_thread		thread;
	t_thread_args	*args;

	mem_zero(&thread, sizeof(t_thread));
	args = make_thread_args(ctx, id);
	if (args == NULL
		|| pthread_create(&thread.handle, NULL, simulate_thread, args) != 0)
		return (thread);
	thread.timestamp = time_now();
	thread.id = id;
	return (thread);
}
