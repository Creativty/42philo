/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:44:09 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/19 10:38:42 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_thread(void *arg)
{
	return ((void)arg, NULL);
}

static t_result_thread make_thread(void *arg)
{
	t_thread	t;
	
	if (pthread_create(&t, NULL, routine_thread, arg) != 0)
		return (RESULT_FAIL(thread, t));
	return (RESULT_OK(thread, t));
}

t_result_person	make_person(long id, void *arg)
{
	t_person		p;
	t_result_thread	t;

	zero((void *)&p, sizeof(t_person));
	if (arg == NULL)
		return (RESULT_FAIL(person, p));
	p.id = id;
	t = make_thread(arg);
	if (!t.ok)
		return (RESULT_FAIL(person, p));
	p.thread = t.data;
	return (RESULT_OK(person, p));
}

void	delete_person(t_result_person p)
{
	if (p.ok)
	{
	}
}
