/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rune.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abderrahim <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:17:24 by abderrahim        #+#    #+#             */
/*   Updated: 2024/12/01 19:29:00 by abderrahim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	rune_is_digit(char rune)
{
	return (('0' ^ rune) < 10);
}

bool	rune_is_space(char rune)
{
	return (rune == '\f' || rune == '\n' || rune == '\r' || rune == '\t'
		|| rune == '\v');
}
