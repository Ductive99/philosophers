/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:12:42 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 02:25:59 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*change_status(t_data *data, int philo_id, int isdead);

static int	check_philosopher_death(t_data *data, int i)
{
	uint64_t	fast_time;
	uint64_t	last_meal;

	pthread_mutex_lock(&data->philos[i].data_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].data_mutex);
	fast_time = get_time_in_ms() - last_meal;
	if (fast_time > (uint64_t)data->time_to_die)
		return (1);
	return (0);
}

static int	check_meal_completion(t_data *data)
{
	int	enough_meals_counter;
	int	i;
	int	meal_count;

	enough_meals_counter = 0;
	i = -1;
	while (++i < data->philosopher_count)
	{
		pthread_mutex_lock(&data->philos[i].data_mutex);
		meal_count = data->philos[i].meal_count;
		pthread_mutex_unlock(&data->philos[i].data_mutex);
		if (data->max_meal_count > 0 && data->max_meal_count <= meal_count)
			enough_meals_counter++;
	}
	return (enough_meals_counter == data->philosopher_count);
}

void	*waiter_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->philosopher_count)
		{
			if (check_philosopher_death(data, i))
				return (change_status(data, i + 1, 1));
		}
		if (check_meal_completion(data))
			return (change_status(data, 0, 0));
		usleep(100);
	}
	return (NULL);
}

static void	*change_status(t_data *data, int philo_id, int isdead)
{
	pthread_mutex_lock(&data->sim_status_mutex);
	data->simulation_over = 1;
	pthread_mutex_unlock(&data->sim_status_mutex);
	if (isdead)
		print_status(data, philo_id, DIED);
	return (NULL);
}
