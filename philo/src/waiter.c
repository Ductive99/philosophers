/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:12:42 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/19 21:08:05 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*waiter_routine(void *arg)
{
	t_data		*data;
	uint64_t	fast_time;
	int			enough_meals_counter;
	int			i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		enough_meals_counter = 0;
		while (++i < data->philosopher_count)
		{
			fast_time = get_time_in_ms() - data->philos[i].last_meal_time;
			if (fast_time > (uint64_t)data->time_to_die)
				return (print_status(data, i + 1, DIED),
					data->simulation_over = 1, NULL);
			if (data->max_meal_count >= data->philos[i].meal_count)
				enough_meals_counter++;
		}
		if (enough_meals_counter == data->philosopher_count)
			return (data->simulation_over = 1, NULL);
		usleep(1000);
	}
	return (NULL);
}
