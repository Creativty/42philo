/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:01:06 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 19:30:24 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <pthread.h>

typedef unsigned long			t_ulong;
typedef pthread_mutex_t			t_mutex;
typedef struct s_data_result	t_data_result;
typedef struct s_parse_result	t_parse_result;

struct s_parse_result
{
	bool	ok;
	t_ulong	count;
	t_ulong	dt_die;
	t_ulong	dt_eat;
	t_ulong	dt_sleep;
	t_ulong	cycles;
};

struct s_data_result
{
	t_parse_result	p;
};

t_parse_result		parse(const int argc, const char **argv);
t_mutex				*mutex_make(t_ulong count);
void				mutex_lock(t_mutex *m);
void				mutex_unlock(t_mutex *m);
void				mutex_delete(t_mutex *m, t_ulong count);

bool				rune_is_space(char rune);
bool				rune_is_digit(char rune);
#endif
