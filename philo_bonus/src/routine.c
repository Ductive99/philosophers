/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 21:39:44 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 05:33:14 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void take_forks(t_philo *philo)
{
	sem_wait(philo->table->room);
	sem_wait(philo->table->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print_status(philo, "has taken a fork");
}

static void eat_and_sleep(t_philo *philo)
{
	uint64_t current_time;

	current_time = get_time_in_ms();
	__atomic_store_n(&philo->last_meal_time, current_time, __ATOMIC_SEQ_CST);
	print_status(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	philo->meal_count++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	sem_post(philo->table->room);
	if (philo->table->max_meal_count != -1 && philo->meal_count >= philo->table->max_meal_count)
	{
		close_semaphores(philo->table);
		exit(0);
	}
	print_status(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void philosopher_routine(t_data *data, int id)
{
	t_philo philo;
	pthread_t monitor;

	philo.id = id;
	philo.table = data;
	philo.meal_count = 0;
	__atomic_store_n(&philo.last_meal_time, get_time_in_ms(), __ATOMIC_SEQ_CST);
	pthread_create(&monitor, NULL, monitor_death, &philo);
	pthread_detach(monitor);
	if (data->philosopher_count == 1)
	{
		print_status(&philo, "has taken a fork");
		while (1)
			usleep(10000);
	}
	if (id % 2 == 0)
		usleep(data->time_to_eat * 500);
	while (1)
	{
		print_status(&philo, "is thinking");
		usleep(500);
		take_forks(&philo);
		eat_and_sleep(&philo);
	}
}
