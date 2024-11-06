/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:55:46 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 11:05:15 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	make_config_test(t_config *cfg, bool do_test_cycles)
{
	if (cfg->population == -1)
		return (false);
	if (cfg->time_die == -1 || cfg->time_eat == -1 || cfg->time_sleep == -1)
		return (false);
	if (do_test_cycles && cfg->cycles == -1)
		return (false);
	return (true);
}

t_config	*make_config(const char **strs, int len)
{
	t_config	*cfg;

	if (len < 1 || len > 5)
		return (NULL);
	cfg = malloc(sizeof(t_config));
	if (cfg)
	{
		cfg->population = strconv_long(strs[0]);
		cfg->time_die = strconv_long(strs[1]);
		cfg->time_eat = strconv_long(strs[2]);
		cfg->time_sleep = strconv_long(strs[3]);
		if (len == 5)
			cfg->cycles = strconv_long(strs[4]);
		else
			cfg->cycles = -1;
	}
	if (make_config_test(cfg, len == 5))
		return (cfg);
	return (free(cfg), NULL);
}
