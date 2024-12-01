/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:01:06 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 20:32:10 by abderrahim       ###   ########.fr       */
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
typedef pthread_t				t_thread;
typedef struct s_person			t_person;
typedef struct s_data_result	t_data_result;
typedef struct s_args_result	t_args_result;

struct s_person
{
	t_ulong			id;
	t_ulong			time_eat;
	t_mutex			*lock_eat;
	t_data_result	*d;
	t_thread		t;
};

struct s_args_result
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
	struct s_args
	{
		t_ulong		count;
		t_ulong		dt_die;
		t_ulong		dt_eat;
		t_ulong		dt_sleep;
		t_ulong		cycles;
		bool		has_cycles;
	}				args;
	t_mutex			*lock_sync;
	t_mutex			*lock_forks;
	t_person		*group;
	bool			ok;
};

t_args_result		args_parse(const int argc, const char **argv);
t_data_result		data_make(t_args_result p, bool has_cycles);
void				data_init(t_data_result *d);
void				data_await(t_data_result *d);
void				data_delete(t_data_result *d);

void				data_group_init(t_data_result *d);

t_person			*group_make(t_ulong	count);
void				*person_routine(void *x);
void				group_delete(t_person *g, t_ulong count);

t_mutex				*mutex_make(t_ulong count);
void				mutex_lock(t_mutex *m);
void				mutex_unlock(t_mutex *m);
void				mutex_delete(t_mutex *m, t_ulong count);

t_thread			thread_start(void *(*f)(void *), t_person *p);
void				thread_await(t_thread t);

bool				rune_is_space(char rune);
bool				rune_is_digit(char rune);

t_ulong				time_now(void);
void				mem_copy(void *src, void *dst, t_ulong len);
void				mem_fill(void *mem, t_ulong len, unsigned char byte);
#endif
