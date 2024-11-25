/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:32:14 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:48:03 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H
# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# define MSG_ERR_ARGS "error: arguments are invalid\n"
# define MSG_ERR_DATA "error: constructor of data failed\n"

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef	unsigned long	t_ulong;

typedef struct s_arguments
{
	long	count;
	long	cycles;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	bool	ok;
}						t_arguments;

typedef struct s_person
{
	long		id;
	long		instant_eat;
	long		instant_start;
	t_thread	thread;
	t_data		*data;
}						t_person;

typedef struct s_data
{
	t_person	*people;
	t_mutex		*forks;
	t_mutex		*sync;
	t_arguments	args;
	bool		ok;
	bool		stop;
}						t_data;

bool		rune_is_sign(char rune);
bool		rune_is_digit(char rune);
bool		rune_is_space(char rune);

void		*routine_thread(t_person *p);
void		make_thread(t_person *p);

t_data		make_data(t_arguments args);
void		prepare_data(t_data *data);
void		await_data(t_data data);
void		delete_data(t_data data);

t_mutex		*make_mutex(t_ulong count);
void		delete_mutex(t_mutex *m, t_ulong count);
void		lock_mutex(t_mutex *m);
void		unlock_mutex(t_mutex *m);

t_person	*make_people(t_ulong count);
void		delete_people(t_person *people);

t_ulong		instant_now(void);
t_ulong		instant_sleep(t_ulong duration_millis);
t_arguments	parse_arguments(const int argc, const char **argv);
#endif
