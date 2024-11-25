/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   people.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:12:27 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:54:59 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_person	*make_people(t_ulong count)
{
	t_ulong		i;
	t_person	*people;

	i = 0ul;
	people = malloc(sizeof(t_person) * count);
	while (people && i < count)
	{
		people[i].id = i + 1;
		people[i].data = NULL;
		people[i].instant_eat = -1;
		people[i].instant_start = -1;
		i++;
	}
	return (people);
}

void	delete_people(t_person *people)
{
	free(people);
}
