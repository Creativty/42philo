/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:55:42 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:39:12 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	main(int argc, char **argv)
{
	t_shared	s;

	// Allocation
	s = make_shared(argc - 1, &argv[1]);
	if (test_shared(s, argc == 6))
		return (fprintf(stderr, "error: wrong arguments\n"), 1);
	print_shared(s);
	/* Old method
		s.count = 3;
		s.death = false;
		s.cycles = -1;
		s.time_eat = 100;
		s.time_sleep = 100;
		s.time_death = 300;
	*/
	{ // Sync lock
		s.sync = malloc(sizeof(t_mutex) * 1);
		if (s.sync == NULL)
			return (fprintf(stderr, "error: malloc `s.sync`\n"), 1);
		pthread_mutex_init(s.sync, NULL);
	}
	{ // Print lock
		s.print = malloc(sizeof(t_mutex) * 1);
		if (s.print == NULL)
			return (fprintf(stderr, "error: malloc `s.print`\n"), 1);
		pthread_mutex_init(s.print, NULL);
	}
	{ // Fork locks
		s.forks = malloc(sizeof(t_mutex) * s.count);
		if (s.forks == NULL)
			return (fprintf(stderr, "error: malloc `s.forks`\n"), 1);
		for (int i = 0; i < s.count; i++)
			pthread_mutex_init(&s.forks[i], NULL);
	}
	{ // People instances
		s.people = malloc(sizeof(t_person) * s.count);
		if (s.people == NULL)
			return (fprintf(stderr, "error: malloc `s.people`\n"), 1);
		for (int i = 0; i < s.count; i++) {
			s.people[i].id = i + 1;
			s.people[i].cycle = 0;
			s.people[i].shared = &s;
			s.people[i].last_eat = -1;
		}
		// People instances threads
		s.instant_start = time_now();
		for (int i = 0; i < s.count; i++)
			pthread_create(&s.people[i].thread, NULL, routine, &s.people[i]);
	}
	for (int i = 0; i < s.count; i++)
		pthread_join(s.people[i].thread, NULL);
	// Deallocation
	for (int i = 0; i < s.count; i++)
		pthread_mutex_destroy(&s.forks[i]);
	pthread_mutex_destroy(s.print);
	pthread_mutex_destroy(s.sync);
	free(s.people);
	free(s.forks);
	free(s.print);
	free(s.sync);
	return (0);
}
