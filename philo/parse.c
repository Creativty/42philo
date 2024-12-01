/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:11:21 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 19:33:50 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool long_fits_int(long n)
{
	return (n <= (long)INT_MAX && n >= (long)INT_MIN);
}

static long parse_param(const char *str)
{
	int		i;
	long	n;
	long	s;

	i = 0;
	n = 0;
	s = 1;
	while (rune_is_space(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			s = s * (-1);
	while (rune_is_digit(str[i]) && long_fits_int(n * s))
		n = (n * 10) + (long)(str[i++] - '0');
	if (i > 0 && str[i] == '\0' && long_fits_int(n * s))
		return (n * s);
	return (-1);
}

static void	try_parse_param(const char *str, t_parse_result *p, t_ulong *out)
{
	long	n;

	if (str == NULL || p == NULL || out == NULL || !p->ok)
		return ;
	n = parse_param(str);
	p->ok = (n >= 0);
	if (p->ok)
		*out = (t_ulong)n;
}

t_parse_result		parse(const int argc, const char **argv)
{
	t_parse_result	p;

	p.ok = (argv != NULL && (argc == 4 || argc == 5));
	try_parse_param(argv[0], &p, &p.count);
	try_parse_param(argv[1], &p, &p.dt_die);
	try_parse_param(argv[2], &p, &p.dt_eat);
	try_parse_param(argv[3], &p, &p.dt_sleep);
	if (argc == 5)
		try_parse_param(argv[4], &p, &p.cycles);
	return (p);
}
