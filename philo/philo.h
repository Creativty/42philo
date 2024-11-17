/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:31:43 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 18:03:31 by aindjare         ###   ########.fr       */
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
# define FMT_PARAMS "( population %ld, time_death %ld, time_eat %ld, time_sleep %ld, cycles %ld )"
# define TYPEDEF_RESULT(NAME) typedef struct s_result_ ## NAME { bool ok; t_ ## NAME data; } t_result_ ## NAME
# define TYPEDEF_BOX(NAME) typedef struct s_box_ ## NAME { bool ok; t_ ## NAME *data; } t_box_ ## NAME
# define RESULT_OK(TYPE, data) (t_result_ ## TYPE){ true, data }
# define RESULT_FAIL(TYPE, data) (t_result_ ## TYPE){ false, data }

typedef pthread_t		t_thread;
TYPEDEF_BOX(thread);

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
	t_thread	thread;
	t_stage		*stage;
}	t_person;
TYPEDEF_RESULT(person);

typedef struct s_stage
{
	long			instant;
	t_result_mutex	*forks;
	t_result_person	*people;
	t_parameters	params;
}	t_stage;
TYPEDEF_RESULT(stage);

t_result_mutex		make_mutex(void);
void				delete_mutex(t_result_mutex m);
void				lock_mutex(t_result_mutex m);
void				unlock_mutex(t_result_mutex m);

t_result_mutex		*make_forks(long count, void *dependency);
t_result_person		*make_people(long count, void *dependency);
t_result_person		make_person(t_result_mutex *forks, long id);

void				delete_person(t_result_person p);
void				delete_people(t_result_person *people, long count);
void				delete_forks(t_result_mutex *forks, long count);

t_result_parameters	make_parameters(int argc, char **argv);
t_stage				make_stage(t_parameters params);
        		
void				*new(unsigned long unit, unsigned long count);
unsigned long		zero(char *region, unsigned long size);

long				now(void);
void				sleep(long ms);
#endif
