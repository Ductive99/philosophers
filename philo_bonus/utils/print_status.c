/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 03:08:01 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 03:08:06 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, char *status)
{
	int	timestamp;

	if (sem_trywait(philo->table->death) == 0)
	{
		sem_post(philo->table->death);
		return ;
	}
	sem_wait(philo->table->write);
	if (sem_trywait(philo->table->death) == 0)
	{
		sem_post(philo->table->death);
		sem_post(philo->table->write);
		return ;
	}
	timestamp = get_time_in_ms() - philo->table->simulation_start_time;
	printf("%d %d %s\n", timestamp, philo->id, status);
	sem_post(philo->table->write);
}
