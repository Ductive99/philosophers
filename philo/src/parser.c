/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 09:56:07 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/03 11:40:57 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	set_int(int *val, char *str);

int	parse(t_data *arg, int argc, char **argv)
{
	int	ret;

	ret = 1;
	if (argc != 5 && argc != 6)
		return (print_error(ERR_ARGC, NULL), 0);
	if (!set_int(&arg->philosopher_count, argv[1]))
		ret = print_error(-1, "philosopher_count\n");
	else if (arg->philosopher_count > 999999)
		ret = print_error(ERR_PHILO_COUNT, NULL);
	if (!set_int(&arg->time_to_die, argv[2]))
		ret = print_error(-1, "time_to_die\n");
	if (!set_int(&arg->time_to_eat, argv[3]))
		ret = print_error(-1, "time_to_eat\n");
	if (!set_int(&arg->time_to_sleep, argv[4]))
		ret = print_error(-1, "time_to_sleep\n");
	if (argc == 6 && !set_int(&arg->max_meal_count, argv[5]))
		ret = print_error(-1, "max_meal_count\n");
	else
		arg->max_meal_count = -1;
	return (ret);
}

static int	set_int(int *val, char *str)
{
	*val = 1000000;
	if (!check_num(str))
		return (print_error(ERR_INVALID_NUMBER, NULL), 0);
	if (!check_int_overflow(str))
		return (print_error(ERR_INT_OVERFLOW, NULL), 0);
	*val = ft_atoi(str);
	if (*val < 0)
		return (print_error(ERR_NEGATIVE_NUMBER, NULL), 0);
	return (1);
}
