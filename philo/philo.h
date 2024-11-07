/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:51:27 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/06 13:59:34 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include "typedefs.h"

t_config	*make_config(const char **strs, int len);	
t_context	*make_context(t_config *cfg);
t_thread	make_thread(t_context *ctx, long id);

void		delete_context(t_context *ctx);
int			simulate_context(t_context *ctx, t_config *cfg);
void		*simulate_thread(void *_args);

// DOCS: returns unix epoch timestamp in milliseconds
long		time_now(void);
// DOCS: zeroes out all the bytes in the memory region
void		mem_zero(void *mem, size_t size);
// DOCS: tests if a rune is a valid digit
bool		rune_is_digit(const char rune);
// DOCS: parses string to long in the region [0, INT_MAX]
long		strconv_long(const char *str);
#endif
