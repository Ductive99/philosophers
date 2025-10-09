/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 04:26:06 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 05:39:15 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int should_die(t_philo *philo)
{
	uint64_t last_meal;

	last_meal = __atomic_load_n(&philo->last_meal_time, __ATOMIC_SEQ_CST);
	return (get_time_in_ms() - last_meal >= (uint64_t)philo->table->time_to_die);
}

void die_and_exit(t_philo *philo)
{
	sem_wait(philo->table->write);
	printf("%ld %d died\n", get_time_in_ms() - philo->table->simulation_start_time, philo->id);
	sem_post(philo->table->write);
	sem_post(philo->table->death);
	close_semaphores(philo->table);
	exit(1);
}

void *monitor_death(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(1000);
		if (should_die(philo))
		{
			sem_wait(philo->table->death);
			sem_wait(philo->table->write);
			printf("%ld %d died\n", get_time_in_ms() - philo->table->simulation_start_time, philo->id);
			sem_post(philo->table->write);
			exit(1);
		}
	}
	return (NULL);
}

void supervisor_routine(t_data *data, pid_t *pids)
{
	int i;
	int status;
	int finished;

	finished = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < data->philosopher_count)
			{
				kill(pids[i], SIGINT);
				i++;
			}
			break;
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			finished++;
			if (finished >= data->philosopher_count)
				break;
		}
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	cleanup_semaphores(data);
}
