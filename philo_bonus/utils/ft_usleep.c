/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:00:00 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/06 04:10:29 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time_in_ms)
{
	uint64_t	start;
	uint64_t	current;

	start = get_time_in_ms();
	current = start;
	while (current - start < (uint64_t)time_in_ms)
	{
		usleep(500);
		current = get_time_in_ms();
	}
}

int	ft_usleep_with_death_check(t_philo *philo, int time_in_ms)
{
	uint64_t	start;
	uint64_t	now;

	start = get_time_in_ms();
	while (1)
	{
		now = get_time_in_ms();
		if (now - philo->last_meal_time > (uint64_t)philo->table->time_to_die)
			return (1);
		if (now - start >= (uint64_t)time_in_ms)
			break ;
		usleep(500);
	}
	return (0);
}
