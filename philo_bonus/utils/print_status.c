/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 03:08:01 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 05:50:39 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, char *status)
{
	int	timestamp;

	sem_wait(philo->table->write);
	timestamp = get_time_in_ms() - philo->table->simulation_start_time;
	printf("%d %d %s\n", timestamp, philo->id, status);
	fflush(stdout);
	sem_post(philo->table->write);
}
