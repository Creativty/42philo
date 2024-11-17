/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:44:09 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 18:02:11 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_thread_result make_thread(void *arg)
{
	t_thread	t;
	
	if (pthread_create(&t, NULL, entry_person, arg) != 0)
		return (RESULT_FAIL(thread, t));
	return (RESULT_OK(thread, t));
}

t_result_person	make_person(t_result_mutex *forks, long id, void *arg)
{
	t_person		p;
	t_thread_result	t;

	zero((void *)&p, sizeof(t_person));
	if (forks == NULL)
		return (RESULT_FAIL(person, p));
	p.id = id;
	p.forks = forks;
	t = make_thread(arg);
	return (RESULT_OK(person, p));
}

void	delete_person(t_result_person p)
{
	if (p.ok)
	{
	}
}
