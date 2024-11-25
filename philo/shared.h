/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:33:36 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:40:06 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H
# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_shared	t_shared;

typedef struct s_person
{
	long		id;
	long		cycle;
	long		last_eat;
	t_thread	thread;
	t_shared	*shared;
}						t_person;

typedef struct s_shared
{
	t_person	*people;
	t_mutex		*print;
	t_mutex		*forks;
	t_mutex		*sync;
	bool		death;
	long		count;
	long		cycles;
	long		instant_start;
	long		time_eat;
	long		time_sleep;
	long		time_death;
}						t_shared;

bool		is_sign(char rune);
bool		is_digit(char rune);
bool		is_space(char rune);
        	
long		math_abs(long a);
long		math_max(long a, long b);
long		math_parse_long(char *str);
        	
void		*routine(void *arg);
bool		routine_eat(t_person *p);
bool		routine_sleep(t_person *p);
bool		routine_think(t_person *p);

void		mem_zero(void *memory, unsigned long size);
long		time_now(void);
void		thread_sleep(long duration_ms);
        	
t_mutex		*person_fork(t_person *p, long delta);
void		person_fork_hold(t_person *p, long delta);
void		person_fork_drop(t_person *p, long delta);
bool		person_do_stop(t_person *p, long timestamp);

t_shared	make_shared(int argc, char **argv);
int			test_shared(t_shared s, bool do_test_cycles);

void		print(t_person *p, char *msg, long timestamp);
void		print_shared(t_shared s);
bool		print_while_alive(t_person *p, char *msg, long timestamp);
#endif
