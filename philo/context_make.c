/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:32:36 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 11:56:05 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_context	*make_context_zero(void)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (ctx)
		mem_zero(ctx, sizeof(t_context));
	return (ctx);
}

static void	*make_context_mutexes_cleanup(t_mutex *mtxs, long count)
{
	long	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&mtxs[i]);
		i++;
	}
	return (free(mtxs), NULL);
}

static t_mutex	*make_context_mutexes(long count)
{
	long	i;
	t_mutex	*mtxs;

	i = 0;
	mtxs = malloc(sizeof(t_mutex) * count);
	if (mtxs == NULL)
		return (NULL);
	while (i < count)
	{
		if (pthread_mutex_init(&mtxs[i], NULL) != 0)
			break ;
		i++;
	}
	if (i < count)
		return (make_context_mutexes_cleanup(mtxs, i));
	return (mtxs);
}

static t_thread	*make_context_threads(long count)
{
	t_thread	*threads;

	threads = malloc(sizeof(t_thread) * count);;
	if (threads)
	{
		mem_zero(threads, sizeof(t_thread) * count);
	}
	return (threads);
}

void	delete_context(t_context *ctx)
{
	make_context_mutexes_cleanup(ctx->forks, ctx->cfg->population);
	pthread_mutex_destroy(&ctx->printf);
	mem_zero(ctx, sizeof(t_context));
	free(ctx);
}

t_context	*make_context(t_config *cfg)
{
	t_context	*ctx;

	if (cfg == NULL)
		return (NULL);
	ctx = make_context_zero();
	if (ctx)
	{
		ctx->cfg = cfg;
		ctx->forks = make_context_mutexes(cfg->population);
		if (ctx->forks == NULL)
			return (free(ctx), NULL);
		if (pthread_mutex_init(&ctx->printf, NULL) != 0)
			return (make_context_mutexes_cleanup(ctx->forks, cfg->population)
				, free(ctx), NULL);
		ctx->threads = make_context_threads(cfg->population);
		ctx->do_simulate = true;
	}
	return (ctx);
}
