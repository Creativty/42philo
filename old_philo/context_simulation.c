/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:05 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 16:41:07 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pre_simulate_context(t_context *ctx, t_config *cfg)
{
	if (ctx == NULL || cfg == NULL)
		return (1);
	mutex_set_bool(&ctx->sync, &ctx->do_wait, false);
	return (0);
}

static int	inner_simulate_context(t_context *ctx, t_config *cfg)
{
	(void)ctx;
	(void)cfg;
	return (0);
}

static int	post_simulate_context(t_context *ctx, t_config *cfg)
{
	long			i;
	t_thread		thread;
	t_thread_args	*args;

	i = 0;
	while (i < cfg->population)
	{
		args = NULL;
		thread = ctx->threads[i++];
		pthread_join(thread.handle, (void *)&args);
		if (args)
			free(args);
	}
	return (0);
}

int	simulate_context(t_context *ctx, t_config *cfg)
{
	int	retval;
	
	if (ctx == NULL)
		return (1);
	retval = pre_simulate_context(ctx, cfg);
	if (retval != 0)
		return (retval);
	retval = inner_simulate_context(ctx, cfg);
	if (retval != 0)
		return (retval);
	retval = post_simulate_context(ctx, cfg);
	if (retval != 0)
		return (retval);
	return (retval);
}
