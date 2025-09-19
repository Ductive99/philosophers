/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:02:05 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/19 03:11:17 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    *philosopher_routine(void *arg)
{
    t_philosopher   *philo;

    philo = (t_philosopher *)arg;
    while (1)
    {
        // Thinking
        print_status(philo->table, philo->id, THINKING);

        // Take forks
        pthread_mutex_lock(philo->left_fork);
        print_status(philo->table, philo->id, TAKING_FORK);
        pthread_mutex_lock(philo->right_fork);
        print_status(philo->table, philo->id, TAKING_FORK);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        usleep(1000);
    }
}
