/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:05 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 11:57:05 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pre_simulate_context(t_context *ctx, t_config *cfg)
{
	((void)ctx, (void)cfg);
	return (0);
}

static int	inner_simulate_context(t_context *ctx, t_config *cfg)
{
	((void)ctx, (void)cfg);
	return (0);
}

int	simulate_context(t_context *ctx, t_config *cfg)
{
	int	retval;
	
	retval = pre_simulate_context(ctx, cfg);
	inner_simulate_context(ctx, cfg);
	return (retval);
}
