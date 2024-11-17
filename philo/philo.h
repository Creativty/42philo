/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:31:43 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 15:52:03 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# define FMT_PARAMS "< population %ld, time_death %ld, time_eat %ld, time_sleep %ld, cycles %ld >"
# define TYPEDEF_RESULT(NAME) typedef struct s_result_ ## NAME { bool ok; t_ ## NAME data; } t_result_ ## NAME
# define TYPEDEF_BOX(NAME) typedef struct s_box_ ## NAME { bool ok; t_ ## NAME *data; } t_box_ ## NAME

typedef pthread_t		t_thread;
TYPEDEF_RESULT(thread);

typedef pthread_mutex_t	t_mutex;
TYPEDEF_RESULT(mutex);

typedef struct s_parameters
{
	long	population;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	cycle_max;
}	t_parameters;
TYPEDEF_RESULT(parameters);

typedef struct s_stage t_stage;

typedef struct s_person
{
	long		id;
	long		last_eat;
	t_mutex		fork;
	t_thread	handle;
	t_stage		*stage;
}	t_person;

typedef struct s_stage
{
	t_mutex			sync;
	t_mutex			start;
	t_person		*people;
	t_parameters	params;
	bool			failure;
}	t_stage;

bool				make_mutex(t_mutex *mutex);
bool				delete_mutex(t_mutex *mutex);
bool				lock_mutex(t_mutex *mutex);
bool				unlock_mutex(t_mutex *mutex);
        		
long				now(void);
void				*new(unsigned long unit, unsigned long count);
t_result_parameters	make_parameters(int argc, char **argv);
#endif
