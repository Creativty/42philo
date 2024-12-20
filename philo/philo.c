/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:47:13 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:32:19 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(const int argc, const char **argv)
{
	t_args_result	args;
	t_data_result	data;

	args = args_parse(argc - 1, &argv[1]);
	if (args.ok == false)
		return (printf("error: could not parse arguments\n"), 1);
	data = data_make(args, (argc - 1) == 5);
	if (data.ok == false)
		return (printf("error: could not prepare the dining table\n"), 1);
	data_init(&data);
	data_await(&data);
	data_delete(&data);
	return (0);
}
