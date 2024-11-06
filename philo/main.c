/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:49:10 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 11:57:53 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_config	*cfg;
	t_context	*ctx;
	int			retval;

	cfg = make_config(&argv[1], argc - 1);
	if (cfg == NULL)
		return (printf("error: invalid arguments.\n"), 1);
	ctx = make_context(cfg);
	if (ctx == NULL)
		return (printf("error: could initialize context\n"), free(cfg), 1);
	printf("unix time: %ld\n", time_now());
	retval = simulate_context(ctx, cfg);
	return (delete_context(ctx), free(cfg), retval);
}
