/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:12:42 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/22 20:09:55 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*change_status(t_data *data, int philo_id, int isdead);

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
				return (change_status(data, i + 1, 1));
			if (data->max_meal_count > 0
				&& data->max_meal_count <= data->philos[i].meal_count)
				enough_meals_counter++;
		}
		if (enough_meals_counter == data->philosopher_count)
			return (change_status(data, i + 1, 0));
		usleep(100);
	}
	return (NULL);
}

static void	*change_status(t_data *data, int philo_id, int isdead)
{
	if (isdead)
		print_status(data, philo_id, DIED);
	pthread_mutex_lock(&data->sim_status_mutex);
	data->simulation_over = 1;
	pthread_mutex_unlock(&data->sim_status_mutex);
	return (NULL);
}
