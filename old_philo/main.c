/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:55:42 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 13:43:11 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	init_people(t_shared *s)
{
	long	i;

	if (s->instant_start == -1)
		return ;
	i = 0;
	while (i < s->count)
	{
		s->people[i].shared = s;
		pthread_create(&s->people[i].thread, NULL, routine, &s->people[i]);
		i++;
	}
}

void	await_people(t_shared *s)
{
	long	i;

	if (s->instant_start == -1)
		return ;
	i = 0;
	while (i < s->count)
		pthread_join(s->people[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_shared	s;

	s = make_shared(argc - 1, &argv[1]);
	init_people(&s);
	await_people(&s);
	return (delete_shared(s), 0);
}
