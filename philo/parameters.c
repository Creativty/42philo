/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:33:30 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 15:51:25 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	parse_parameter(char *arg)
{
	long	n;

	n = atol(arg);
	if (n < 0 || n > INT_MAX)
		return (-1);
	return (n);
}

#define RESULT_OK(TYPE, data) (t_result_ ## TYPE){ true, data }
#define RESULT_FAIL(TYPE, data) (t_result_ ## TYPE){ false, data }

static bool	make_parameters_failure(t_parameters params, int argc)
{
	if (params.population == -1 || params.time_die == -1)
		return (true);
	if (params.time_eat == -1 || params.time_sleep == -1)
		return (true);
	if (argc == 5 && params.cycle_max == -1)
		return (true);
	return (false);
}

t_result_parameters	make_parameters(int argc, char **argv)
{
	t_parameters	params;

	bzero(&params, sizeof(t_parameters)); // TODO(XENOBAS): polyfill
	if (argc != 4 && argc != 5)
		return (RESULT_FAIL(parameters, params));
	params.population = parse_parameter(argv[0]);
	params.time_die = parse_parameter(argv[1]);
	params.time_eat = parse_parameter(argv[2]);
	params.time_sleep = parse_parameter(argv[3]);
	params.cycle_max = -1;
	if (argc == 5)
		params.cycle_max = parse_parameter(argv[4]);
	if (make_parameters_failure(params, argc))
		return (RESULT_FAIL(parameters, params));
	return (RESULT_OK(parameters, params));
}
