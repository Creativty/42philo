/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:07 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/19 10:37:14 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_stage	*make_stage(t_parameters params)
{
	t_stage	*stage;

	stage = new(sizeof(t_stage), 1);
	if (stage)
	{
		stage->forks = make_forks(params.population, stage);
		stage->people = make_people(params.population, stage, stage->forks);
		stage->params = params;
		stage->instant = now();
	}
	return (stage);
}

int	main(int argc, char **argv)
{
	t_stage				*stage;
	t_result_parameters	params;

	params = make_parameters(argc - 1, &argv[1]);
	if (!params.ok)
		return (printf("[error]: incorrect arguments\n"), 1);
	printf("[debug]: parameters "FMT_PARAMS"\n",
		params.data.population, params.data.time_die, params.data.time_eat,
		params.data.time_sleep, params.data.cycle_max);
	stage = make_stage(params.data);
	if (stage == NULL)
		return (printf("[error]: could not allocate the table\n"), 1);
	printf("[debug]: instant %ld\n", stage->instant);
	// forks = make_forks(params.data.population);
	// if (forks == NULL)
	// 	return (printf("[error]: allocation failure\n"), 1);
	// delete_forks(forks, params.data.population);

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
