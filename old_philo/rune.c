/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rune.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:36:38 by aindjare          #+#    #+#             */
/*   Updated: 2024/11/25 10:41:48 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

bool	is_space(char rune)
{
	return (rune == ' ' || rune == '\n' || rune == '\r'
		|| rune == '\v' || rune == '\f');
}

bool	is_sign(char rune)
{
	return (rune == '+' || rune == '-');
}

bool	is_digit(char rune)
{
	return (rune >= '0' && rune <= '9');
}
