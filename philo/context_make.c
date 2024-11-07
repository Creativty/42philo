/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:32:36 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 16:40:00 by aindjare         ###   ########.fr       */
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
		if (!mutex_create(&mtxs[i]))
			break ;
		i++;
	}
	if (i < count)
		return (make_context_mutexes_cleanup(mtxs, i));
	return (mtxs);
}

static void	*make_context_threads_cleanup(t_context *ctx, t_thread *threads,
											bool do_free)
{
	ctx->do_simulate = false;
	ctx->do_wait = false;
	if (do_free)
		return (free(threads), NULL);
	return (threads);
}

static t_thread	*make_context_threads(t_context *ctx, long count)
{
	long		i;
	t_thread	*threads;

	threads = malloc(sizeof(t_thread) * count);
	if (threads)
	{
		i = 0;
		mem_zero(threads, sizeof(t_thread) * count);
		while (i < count)
		{
			threads[i] = make_thread(ctx, i + 1l);
			if (threads[i].id != i + 1l)
				break ;
			i++;
		}
		if (i != count)
			return (make_context_threads_cleanup(ctx, threads, true));
	}
	return (threads);
}

void	delete_context(t_context *ctx)
{
	make_context_mutexes_cleanup(ctx->forks, ctx->cfg->population);
	make_context_threads_cleanup(ctx, ctx->threads, true);
	pthread_mutex_destroy(&ctx->printf);
	pthread_mutex_destroy(&ctx->sync);
	mem_zero(ctx, sizeof(t_context));
	free(ctx);
}

t_context	*make_context(t_config *cfg)
{
	t_context	*ctx;

	ctx = NULL;
	if (cfg)
		ctx = make_context_zero();
	if (ctx)
	{
		ctx->cfg = cfg;
		ctx->forks = make_context_mutexes(cfg->population);
		if (ctx->forks == NULL)
			return (free(ctx), NULL);
		if (!mutex_create(&ctx->printf))
			return (make_context_mutexes_cleanup(ctx->forks, cfg->population)
				, free(ctx), NULL);
		if (!mutex_create(&ctx->sync))
			return (pthread_mutex_destroy(&ctx->sync),
				make_context_mutexes_cleanup(ctx->forks, cfg->population)
				, free(ctx), NULL);
		mutex_lock(&ctx->sync);
			ctx->do_wait = true;
			ctx->do_simulate = true;
		mutex_unlock(&ctx->sync);
		ctx->threads = make_context_threads(ctx, cfg->population);
	}
	return (ctx);
}
