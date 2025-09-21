/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:02:05 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/21 04:36:27 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		print_status(philo->table, philo->id, THINKING);
		take_forks(philo);
		if (!(eat(philo) && sleepy(philo)))
			break ;
		if (philo->table->simulation_over)
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	eat(t_philosopher *philo)
{
	uint64_t	start;

	start = get_time_in_ms();
	print_status(philo->table, philo->id, EATING);
	philo->last_meal_time = get_time_in_ms();
	philo->meal_count++;
	while ((get_time_in_ms() - start) < (uint64_t)philo->table->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (!philo->table->simulation_over);
}

int	sleepy(t_philosopher *philo)
{
	int	start;

	start = 0;
	print_status(philo->table, philo->id, SLEEPING);
	while ((get_time_in_ms() - start) < (uint64_t)philo->table->time_to_sleep
		&& !philo->table->simulation_over)
	{
		usleep(100);
	}
	return (!philo->table->simulation_over);
}

void	take_forks(t_philosopher *philo)
{
	if (philo->table->philosopher_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, TAKING_FORK);
		while (!philo->table->simulation_over)
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	else if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->id, TAKING_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, TAKING_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->id, TAKING_FORK);
	}
}
