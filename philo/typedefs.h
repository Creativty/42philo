/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:31 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 13:46:56 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TYPEDEFS_H
# define TYPEDEFS_H

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
	long		id;
	long		timestamp;
	pthread_t	handle;
}	t_thread;

typedef struct s_context
{
	t_config	*cfg;
	t_thread	*threads;
	t_mutex		*forks;
	t_mutex		printf;
	bool		do_simulate;
	bool		do_wait;
}	t_context;

typedef struct s_thread_args
{
	long		id;
	t_context	*ctx;
}	t_thread_args;
#endif
