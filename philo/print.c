/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:34:05 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:38:40 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	print(t_person *p, char *msg, long timestamp)
{
	t_mutex		*lock;

	lock = p->shared->print;
	pthread_mutex_lock(lock);
	printf("%ld %ld %s\n", timestamp - p->shared->instant_start, p->id, msg);
	pthread_mutex_unlock(lock);
}

bool	print_while_alive(t_person *p, char *msg, long timestamp)
{
	if (person_do_stop(p, timestamp) == false)
		return (print(p, msg, timestamp), false);
	return (true);
}
