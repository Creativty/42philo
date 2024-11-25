/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:29:00 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 15:35:40 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	main(const int argc, const char **argv)
{
	t_arguments	args;
	t_data		data;

	args = parse_arguments(argc - 1, &argv[1]);
	if (!args.ok)
		return (printf(MSG_ERR_ARGS), 1);
	data = make_data(args);
	if (!data.ok)
		return (printf(MSG_ERR_DATA), delete_data(data), 1);
	prepare_data(&data);
	await_data(data);
	return (delete_data(data), 0);
}
