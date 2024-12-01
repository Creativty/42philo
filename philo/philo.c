/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:47:13 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 19:31:24 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(const int argc, const char **argv)
{
	t_parse_result	res;

	res = parse(argc - 1, &argv[1]);
	if (res.ok == false)
		return (printf("error: could not parse arguments\n"), 1);
	return (0);
}
