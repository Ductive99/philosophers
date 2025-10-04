/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int_overflow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:15:01 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/03 10:58:44 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	num_length(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (str[len] >= '0' && str[len] <= '9')
		len++;
	return (len);
}

int	check_int_overflow(char *str)
{
	char	*_int;
	int		len;
	int		i;

	i = -1;
	len = num_length(str);
	if (len < 10)
		return (1);
	if (len > 10)
		return (0);
	_int = "2147483647";
	while (*str == ' ')
		str++;
	len = -1;
	if (*str == '-' || *str == '+')
		len++;
	while (_int[++i] && ++len < 9)
		if (_int[i] < str[len])
			return (0);
	return ((_int[9] + (int)(*str == '-')) >= \
		str[len + (int)(*str == '-')]);
}
