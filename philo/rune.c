/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rune.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:30:40 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 14:33:12 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

bool	rune_is_space(char rune)
{
	return (rune == ' ' || rune == '\f' || rune == '\n'
		|| rune == '\r' || rune == '\t' || rune == '\v');
}

bool	rune_is_digit(char rune)
{
	return (rune >= '0' && rune <= '9');
}

bool	rune_is_sign(char rune)
{
	return (rune == '-' || rune == '+');
}
