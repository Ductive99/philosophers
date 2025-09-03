/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:57:18 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/03 11:00:13 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * check_input - checks if a given string is a number or list of numbers
 *
 * @str: the number or list of numbers as a string
 *
 * Return: 1 if the input is good and well formatted number, 0 otherwise
 */
int	check_num(char *str)
{
	int	n;
	int	d;

	n = 0;
	while (str && *str)
	{
		d = 0;
		while (*str == ' ')
			str++;
		if (*str == '-' || *str == '+')
		{
			++str;
			if (!(*str >= '0' && *str <= '9'))
				return (0);
		}
		while (*str >= '0' && *str <= '9')
		{
			d = 1;
			str++;
		}
		if (*str && *str != ' ')
			return (0);
		n += d;
	}
	return (n);
}
