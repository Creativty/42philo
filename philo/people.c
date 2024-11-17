/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   people.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:41:16 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/17 17:58:22 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_people(t_result_person *people, long count)
{
	long	i;

	if (people)
	{
		i = 0;
		while (i < count)
			delete_person(people[i++]);
		free(people);
	}
}

t_result_person	*make_people(long count, void *dependency)
{
	long			i;
	t_result_person	*people;

	if (dependency == NULL)
		return (NULL);
	people = new(sizeof(t_result_person), count);
	if (people)
	{
		i = 0;
		while (i < count)
		{
			people[i] = make_person(i + 1);
			i++;
		}
	}
	return (people);
}
