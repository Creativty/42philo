/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:29:13 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:19:50 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static long	parse_long(const char *arg)
{
	int		i;
	long	n;
	long	sign;

	i = 0;
	n = 0;
	sign = 1;
	if (arg == NULL)
		return (-1);
	while (rune_is_space(arg[i]))
		i++;
	while (rune_is_sign(arg[i]))
		if (arg[i++] == '-')
			sign *= -1;
	while (rune_is_digit(arg[i]))
		n = ((n * 10) + (long)(arg[i++] - '0'));
	if (i == 0 || arg[i] != '\0' || n < (long)INT_MIN || n > (long)INT_MAX)
		return (-1);
	return (n);
}

static t_arguments	parse_arguments_verify(t_arguments args, const int argc)
{
	if (argc == 5 || argc == 4)
		args.ok = true;
	if (args.ok
		&& (args.count == -1 || args.t_die == -1
			|| args.t_eat == -1 || args.t_sleep == -1))
		args.ok = false;
	if (args.ok && argc == 5 && args.cycles == -1)
		args.ok = false;
	return (args);
}

t_arguments parse_arguments(const int argc, const char **argv)
{
	t_arguments	args;
	
	if (argc >= 4)
	{
		args.count = parse_long(argv[0]);
		args.t_die = parse_long(argv[1]);
		args.t_eat = parse_long(argv[2]);
		args.t_sleep = parse_long(argv[3]);
	}
	if (argc >= 5)
		args.cycles = parse_long(argv[4]);
	return (parse_arguments_verify(args, argc));
}
