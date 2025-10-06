/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 21:39:44 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/06 04:33:18 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	release_forks_and_die(t_data *data, t_philo *philo, int fork_count)
{
	while (fork_count-- > 0)
		sem_post(data->forks);
	die_and_exit(philo);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_status(philo, "has taken a fork");
	if (should_die(philo))
		release_forks_and_die(philo->table, philo, 1);
	sem_wait(philo->table->forks);
	print_status(philo, "has taken a fork");
	if (should_die(philo))
		release_forks_and_die(philo->table, philo, 2);
}

static void	eat_and_sleep(t_philo *philo)
{
	print_status(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	if (ft_usleep_with_death_check(philo, philo->table->time_to_eat) == 1)
		release_forks_and_die(philo->table, philo, 2);
	philo->meal_count++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	if (philo->table->max_meal_count != -1
		&& philo->meal_count >= philo->table->max_meal_count)
	{
		close_semaphores(philo->table);
		exit(0);
	}
	print_status(philo, "is sleeping");
	if (ft_usleep_with_death_check(philo, philo->table->time_to_sleep) == 1)
		die_and_exit(philo);
}

void	philosopher_routine(t_data *data, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.table = data;
	philo.meal_count = 0;
	philo.last_meal_time = get_time_in_ms();
	if (data->philosopher_count == 1)
	{
		print_status(&philo, "has taken a fork");
		ft_usleep_with_death_check(&philo, data->time_to_die);
		die_and_exit(&philo);
	}
	if (id % 2 == 0)
		usleep(1000);
	while (1)
	{
		print_status(&philo, "is thinking");
		usleep(500);
		if (should_die(&philo))
			die_and_exit(&philo);
		take_forks(&philo);
		eat_and_sleep(&philo);
	}
}
