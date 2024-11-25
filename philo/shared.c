/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:37:59 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:38:02 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_shared	make_shared(int argc, char **argv)
{
	t_shared	shared;

	mem_zero(&shared, sizeof(t_shared));
	shared.count = -1;
	shared.time_eat = -1;
	shared.time_death = -1;
	shared.time_sleep = -1;
	shared.cycles = -1;
	if (argc == 4 || argc == 5)
	{
		shared.count = math_parse_long(argv[0]);
		shared.time_death = math_parse_long(argv[1]);
		shared.time_sleep = math_parse_long(argv[2]);
		shared.time_eat = math_parse_long(argv[3]);
	}
	if (argc == 5)
		shared.cycles = math_parse_long(argv[4]);
	return (shared);
}

int	test_shared(t_shared s, bool do_test_cycles)
{
	if (do_test_cycles && s.cycles == -1)
		return (true);
	return (s.count == -1 || s.time_eat == -1
			|| s.time_death == -1 || s.time_sleep == -1);
}

void	print_shared(t_shared s)
{
	printf("< count = %ld,", s.count);
	printf(" time_death = %ld,", s.time_death);
	printf(" time_eat = %ld,", s.time_eat);
	printf(" time_sleep = %ld,", s.time_sleep);
	printf(" cycles = %ld >\n", s.cycles);
}
