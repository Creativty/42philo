/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:07 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 15:51:10 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread(t_thread thread)
{
	pthread_join(thread, NULL);
}

int	main(int argc, char **argv)
{
	// t_stage			*stage;
	t_result_parameters	params;

	// Parse arguments
		// check arguments length to be in range [4, 5]
		// atol on all arguments with -1 representing failure
	params = make_parameters(argc - 1, &argv[1]);
	// Verify arguments
		// if error stop program
	if (!params.ok)
		return (printf("[error]: incorrect arguments\n"), 1);
	printf("[debug]: parameters "FMT_PARAMS"\n",
			params.data.population, params.data.time_die, params.data.time_eat,
			params.data.time_sleep, params.data.cycle_max);
	// Create table
		// people is an array of { fork, id, eat_stamp }
		// sync lock dedicated for all actions that are to be visible
		// start lock
	// Make people alive
		// wait on start lock (people's perspective)
		// turn on start lock (main thread perspective)
	// Simulate people
		// pick fork if all is alive
		// pick fork if all is alive
		// start eating if all is alive
		// start sleeping if all is alive
		// start thinking if all is alive
		// if someone is dead stop
	// Clean up the table
		// destroy all locks (sync, start, forks)
		// destroy people array
	return (0);
}
