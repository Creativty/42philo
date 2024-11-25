/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:37:59 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 11:03:14 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_shared	make_shared_from_args(int argc, char **argv)
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

t_shared	make_shared(int argc, char **argv)
{
	t_shared	s;

	s = make_shared_from_args(argc, argv);
	if (test_shared(s, argc == 6))
		return (fprintf(stderr, "error: wrong arguments\n"), s);
	s.sync = make_mutex(1);
	s.print = make_mutex(1);
	s.forks = make_mutex(s.count);
	s.people = make_people(s.count);
	s.instant_start = time_now();
	if (s.sync == NULL || s.print == NULL
		|| s.forks == NULL || s.people == NULL)
		s.instant_start = -1;
	return (s);
}

void	delete_shared(t_shared s)
{
	delete_mutexes(s.forks, s.count);
	delete_mutexes(s.print, 1);
	delete_mutexes(s.sync, 1);
	free(s.people);
	free(s.forks);
	free(s.print);
	free(s.sync);
}

void	print_shared(t_shared s)
{
	printf("< count = %ld,", s.count);
	printf(" time_death = %ld,", s.time_death);
	printf(" time_eat = %ld,", s.time_eat);
	printf(" time_sleep = %ld,", s.time_sleep);
	printf(" cycles = %ld >\n", s.cycles);
}
