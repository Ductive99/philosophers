/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:40:14 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/22 20:09:47 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_data *data, int philo_id, t_status status)
{
	uint64_t	currenttime;
	int			over;

	currenttime = get_time_in_ms() - data->simulation_start_time;
	pthread_mutex_lock(&data->print_mutex);
	if (status == DIED)
	{
		printf("%lu %d died\n", currenttime, philo_id);
		return ;
	}
	pthread_mutex_lock(&data->sim_status_mutex);
	over = data->simulation_over;
	pthread_mutex_unlock(&data->sim_status_mutex);
	if (over == 1)
		return ;
	if (status == THINKING)
		printf("%lu %d is thinking\n", currenttime, philo_id);
	else if (status == EATING)
		printf("%lu %d is eating\n", currenttime, philo_id);
	else if (status == SLEEPING)
		printf("%lu %d is sleeping\n", currenttime, philo_id);
	else if (status == TAKING_FORK)
		printf("%lu %d has taken a fork\n", currenttime, philo_id);
	pthread_mutex_unlock(&data->print_mutex);
}
