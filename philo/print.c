/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:34:05 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 13:53:34 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static void print_char(char c)
{
	write(1, &c, 1);
}

static void print_number(long x)
{
	if (x < 0)
		print_char('-');
	else if (x < 10)
		print_char("0123456789"[x]);
	else
	{
		print_number(x / 10);
		print_number(x % 10);
	}
}

static void	print_string(const char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		str = "(null)";
	while (str[len])
		len++;
	write(1, str, len);
}

static void print_line(long timestamp, long id, const char *msg)
{
	print_number(timestamp);
	write(1, " ", 1);
	print_number(id);
	write(1, " ", 1);
	print_string(msg);
	write(1, "\n", 1);
}

void	print(t_person *p, char *msg, long timestamp)
{
	t_mutex		*lock;

	lock = p->shared->print;
	pthread_mutex_lock(lock);
	print_line(timestamp - p->shared->instant_start, p->id, msg);
	// printf("%ld %ld %s\n", timestamp - p->shared->instant_start, p->id, msg);
	pthread_mutex_unlock(lock);
}

bool	print_while_alive(t_person *p, char *msg, long timestamp)
{
	if (person_do_stop(p, timestamp) == false)
		return (print(p, msg, timestamp), false);
	return (true);
}
