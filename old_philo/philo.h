/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:51:27 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/07 14:48:26 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define PRINT_FORK "has taken a fork"
# define PRINT_EAT "is eating"
# define PRINT_SLEEP "is sleeping"
# define PRINT_THINK "is thinking"
# define PRINT_DEATH "died"
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include "typedefs.h"

t_config		*make_config(const char **strs, int len);	
t_context		*make_context(t_config *cfg);
t_thread		make_thread(t_context *ctx, long id);

void			delete_context(t_context *ctx);
int				simulate_context(t_context *ctx, t_config *cfg);
t_thread_args	*simulate_thread(t_thread_args *args);

bool			thread_create(pthread_t *handle, t_thread_fn fn,
					t_thread_args *args);
bool			mutex_create(t_mutex *mutex);
void			mutex_lock(t_mutex *mutex);
void			mutex_unlock(t_mutex *mutex);
bool			mutex_get_bool(t_mutex *mutex, bool *identifier);
bool			mutex_set_bool(t_mutex *mutex, bool *identifier, bool value);

// DOCS: returns unix epoch timestamp in milliseconds
long			time_now(void);
// DOCS: zeroes out all the bytes in the memory region
void			mem_zero(void *mem, size_t size);
// DOCS: tests if a rune is a valid digit
bool			rune_is_digit(const char rune);
// DOCS: parses string to long in the region [0, INT_MAX]
long			strconv_long(const char *str);
// DOCS: prints a philosophers-format message
void			print(t_mutex *lock, long id, const char *msg);
// DOCS: sleeps a thread for the duration specified in milliseconds
void			thread_sleep(long duration);
#endif
