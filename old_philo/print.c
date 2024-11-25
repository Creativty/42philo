/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:34:05 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 14:23:41 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

// static void print_char(char c)
// {
// 	write(1, &c, 1);
// }
// 
// static void print_number(long x)
// {
// 	if (x < 0)
// 		print_char('-');
// 	else if (x < 10)
// 		print_char("0123456789"[x]);
// 	else
// 	{
// 		print_number(x / 10);
// 		print_number(x % 10);
// 	}
// }
// 
// static void	print_string(const char *str)
// {
// 	int	len;
// 
// 	len = 0;
// 	if (str == NULL)
// 		str = "(null)";
// 	while (str[len])
// 		len++;
// 	write(1, str, len);
// }
// 
// static void print_line(long timestamp, long id, const char *msg)
// {
// 	print_number(timestamp);
// 	write(1, " ", 1);
// 	print_number(id);
// 	write(1, " ", 1);
// 	print_string(msg);
// 	write(1, "\n", 1);
// }

void	print(t_person *p, char *msg, long timestamp)
{
	t_mutex		*lock_print;
	t_mutex		*lock_sync;

	lock_print = p->shared->print;
	lock_sync = p->shared->sync;
	pthread_mutex_lock(lock_print);
	pthread_mutex_lock(lock_sync);
	if (p->shared->death == false)
		printf("%ld %ld %s\n", timestamp - p->shared->instant_start, p->id, msg);
	pthread_mutex_unlock(lock_sync);
	pthread_mutex_unlock(lock_print);
}

void	print_death(t_person *p, char *msg, long timestamp)
{
	t_mutex		*lock_print;

	(void)msg;
	lock_print = p->shared->print;
	pthread_mutex_lock(lock_print);
	printf("%ld %ld has died\n", timestamp - p->shared->instant_start, p->id);
	pthread_mutex_unlock(lock_print);
}

// bool	print_while_alive(t_person *p, char *msg, long timestamp)
// {
// 	if (person_do_stop(p, timestamp) == false)
// 		return (print(p, msg, timestamp), false);
// 	return (true);
// }
