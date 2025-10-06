/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 04:26:06 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/06 04:28:39 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	should_die(t_philo *philo)
{
	return (get_time_in_ms()
		- philo->last_meal_time > (uint64_t)philo->table->time_to_die);
}

void	die_and_exit(t_philo *philo)
{
	sem_wait(philo->table->write);
	printf("%ld %d died\n", get_time_in_ms()
		- philo->table->simulation_start_time, philo->id);
	sem_post(philo->table->write);
	sem_post(philo->table->death);
	close_semaphores(philo->table);
	exit(1);
}

void	supervisor_routine(t_data *data, pid_t *pids)
{
	int	status;
	int	finished_count;

	finished_count = 0;
	while (waitpid(-1, &status, 0) != -1 && WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			kill_all_processes(pids, data->philosopher_count);
			break ;
		}
		if (WEXITSTATUS(status) == 0 && data->max_meal_count != -1
			&& ++finished_count >= data->philosopher_count)
		{
			kill_all_processes(pids, data->philosopher_count);
			break ;
		}
	}
	while (waitpid(-1, &status, WNOHANG) > 0)
		;
	cleanup_semaphores(data);
}
