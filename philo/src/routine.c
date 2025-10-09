/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:02:05 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 02:32:31 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_simulation_over(t_philosopher *philo)
{
	int	over;

	pthread_mutex_lock(&philo->table->sim_status_mutex);
	over = philo->table->simulation_over;
	pthread_mutex_unlock(&philo->table->sim_status_mutex);
	return (over);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (check_simulation_over(philo))
			break ;
		print_status(philo->table, philo->id, THINKING);
		if (take_forks(philo, get_time_in_ms()))
		{
			if (!eat(philo) || !sleepy(philo))
				break ;
		}
		else if (check_simulation_over(philo))
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	eat(t_philosopher *philo)
{
	uint64_t	start;
	int			over;

	start = get_time_in_ms();
	print_status(philo->table, philo->id, EATING);
	pthread_mutex_lock(&philo->data_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data_mutex);
	while ((get_time_in_ms() - start) < (uint64_t)philo->table->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->table->sim_status_mutex);
	over = philo->table->simulation_over;
	pthread_mutex_unlock(&philo->table->sim_status_mutex);
	return (!over);
}

int	sleepy(t_philosopher *philo)
{
	uint64_t	start;
	int			over;

	start = get_time_in_ms();
	print_status(philo->table, philo->id, SLEEPING);
	while ((get_time_in_ms() - start) < (uint64_t)philo->table->time_to_sleep)
	{
		pthread_mutex_lock(&philo->table->sim_status_mutex);
		over = philo->table->simulation_over;
		pthread_mutex_unlock(&philo->table->sim_status_mutex);
		if (over)
			return (0);
		usleep(100);
	}
	return (1);
}

int	take_forks(t_philosopher *philo, uint64_t fork_start)
{
	if (philo->table->philosopher_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, TAKING_FORK);
		while (get_time_in_ms()
			- fork_start < (uint64_t)philo->table->time_to_die)
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
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
	return (1);
}
