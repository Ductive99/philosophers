/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 21:49:06 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/06 04:11:14 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_status(t_philo *philo, char *status)
{
	int	timestamp;

	sem_wait(philo->table->write);
	timestamp = get_time_in_ms() - philo->table->simulation_start_time;
	printf("%d %d %s\n", timestamp, philo->id, status);
	sem_post(philo->table->write);
}
