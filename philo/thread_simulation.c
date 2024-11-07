/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:16:23 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 16:41:00 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool simulate_thread_test_life(t_thread_args *args)
{
	t_config	*cfg;
	t_context	*ctx;
	t_thread	*thread;

	ctx = args->ctx;
	cfg = args->ctx->cfg;
	thread = &ctx->threads[args->id - 1];
	if (time_now() - thread->timestamp >= cfg->time_die)
	{
		if (mutex_get_bool(&ctx->sync, &ctx->do_simulate))
		{
			mutex_set_bool(&ctx->sync, &ctx->do_simulate, false);
			print(&ctx->printf, args->id, PRINT_DEATH);
		}
		return (false);
	}
	return (true);
}

static bool	simulate_thread_test(t_thread_args *args, long cycle)
{
	t_config	*cfg;
	t_context	*ctx;

	ctx = args->ctx;
	cfg = args->ctx->cfg;
	if (!mutex_get_bool(&ctx->sync, &ctx->do_simulate))
		return (false);
	if (!simulate_thread_test_life(args))
		return (false);
	return (cfg->cycles == -1 || cycle < cfg->cycles);
}

static void	simulate_thread_wait(t_thread_args *args)
{
	t_context	*ctx;

	ctx = args->ctx;
	while (mutex_get_bool(&ctx->sync, &ctx->do_wait))
		;
	// if (args->id % 2)
	// 	thread_sleep(ctx->cfg->time_eat / 10);
}

bool	simulate_fork(t_thread_args *args, long dx, bool do_hold)
{
	t_mutex		*fork;
	t_context	*ctx;

	ctx = args->ctx;
	fork = &ctx->forks[(args->id + dx) % ctx->cfg->population];
	if (do_hold)
	{
		mutex_lock(fork);
		if (!simulate_thread_test(args, 0))
			return (false);
		print(&ctx->printf, args->id, PRINT_FORK);
	}
	else
	{
		mutex_unlock(fork);
	}
	return (simulate_thread_test(args, 0));
}

bool	simulate_eat(t_thread_args *args)
{
	long		dx;
	t_context	*ctx;
	t_config	*cfg;
	t_thread	*thread;

	dx = -1;
	ctx = args->ctx;
	cfg = ctx->cfg;
	thread = &ctx->threads[args->id - 1];
	if (args->id % 2)
		dx = 0;
	if (!simulate_fork(args, dx, true))
		return (simulate_fork(args, dx, false), false);
	if (!simulate_fork(args, dx + 1, true))
		return (simulate_fork(args, dx, false), simulate_fork(args, dx + 1, false), false);
	if (simulate_thread_test(args, 0))
		print(&ctx->printf, args->id, PRINT_EAT);
	thread_sleep(cfg->time_eat);
	thread->timestamp = time_now();
	simulate_fork(args, dx + 1, false);
	simulate_fork(args, dx, false);
	return (simulate_thread_test(args, 0));
}

bool	simulate_sleep(t_thread_args *args)
{
	t_context	*ctx;

	ctx = args->ctx;
	if (simulate_thread_test(args, 0))
		print(&ctx->printf, args->id, PRINT_SLEEP);
	thread_sleep(args->ctx->cfg->time_sleep);
	return (simulate_thread_test(args, 0));
}

bool	simulate_think(t_thread_args *args)
{
	t_context	*ctx;

	ctx = args->ctx;
	print(&ctx->printf, args->id, PRINT_THINK);
	thread_sleep(1);
	return (simulate_thread_test(args, 0));
}

t_thread_args	*simulate_thread(t_thread_args *args)
{
	int			i;
	long		cycle;
	bool		(* const funcs[3])(t_thread_args *) =
	{
		simulate_eat,
		simulate_sleep,
		simulate_think,
	};

	i = 0;
	cycle = 0;
	simulate_thread_wait(args);
	while (simulate_thread_test(args, cycle))
	{
		if (!funcs[i](args))
			break ;
		if (i == 0)
			cycle++;
		i = (i + 1) % 3;
	}
	return (args);
}
