/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:51:27 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 12:00:22 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_config
{
	long	population;
	long	time_eat;
	long	time_die;
	long	time_sleep;
	long	cycles;
}	t_config;

typedef struct s_thread
{
	size_t		id;
	size_t		timestamp;
	pthread_t	handle;
}	t_thread;

typedef struct s_context
{
	t_config	*cfg;
	t_thread	*threads;
	t_mutex		*forks;
	t_mutex		printf;
	bool		do_simulate;
}	t_context;

t_config	*make_config(const char **strs, int len);	
t_context	*make_context(t_config *cfg);
void		delete_context(t_context *ctx);
int			simulate_context(t_context *ctx, t_config *cfg);

// DOCS: returns unix epoch timestamp in milliseconds
long		time_now(void);
// DOCS: zeroes out all the bytes in the memory region
void		mem_zero(void *mem, size_t size);
// DOCS: tests if a rune is a valid digit
bool		rune_is_digit(const char rune);
// DOCS: parses string to long in the region [0, INT_MAX]
long		strconv_long(const char *str);
#endif
