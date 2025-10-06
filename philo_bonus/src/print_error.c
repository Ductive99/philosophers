/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:48:15 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/17 19:25:29 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	load_error_message(char err[6][200]);

int	print_error(t_error_code code, char *str)
{
	char	err_msg[6][200];

	load_error_message(err_msg);
	if (code != (t_error_code)-1)
		ft_putstr_fd(err_msg[code], 2);
	if (str)
		ft_putstr_fd(str, 2);
	return (-1);
}

static void	load_error_message(char err[6][200])
{
	ft_strncpy(err[ERR_ARGC],
		"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
		200);
	ft_strncpy(err[ERR_INVALID_NUMBER], "Invalid Number Error: ", 200);
	ft_strncpy(err[ERR_INT_OVERFLOW], "Int Overflow Error: ", 200);
	ft_strncpy(err[ERR_NEGATIVE_NUMBER],
		"Negative Numbers Don't Make Sense Error: ", 200);
	ft_strncpy(err[ERR_PHILO_COUNT],
		"Invalid Philosopher Count Error\n"
		"\tAccepted Range: 1 -> 255 (included)\n",
		200);
}
