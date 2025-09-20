/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:02:05 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/20 16:36:47 by esouhail         ###   ########.fr       */
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
        take_forks(philo);
        
        // Eat
        eat(philo);
        
        // Sleep
        sleepy(philo);
        
        usleep(1000);
        if (philo->table->simulation_over)
            break ;
        // if (philo->meal_count == philo->table->max_meal_count)
            // break;
    }
    return (NULL);
}

void    eat(t_philosopher *philo)
{
    print_status(philo->table, philo->id, EATING);
    philo->last_meal_time = get_time_in_ms();
    philo->meal_count++;
    usleep(philo->table->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    sleepy(t_philosopher *philo)
{
    int    sleep;

    sleep = 0;
    print_status(philo->table, philo->id, SLEEPING);
    while (sleep / 10 < philo->table->time_to_sleep)
    {
        usleep(100);
        sleep += 1;
    }
    // usleep(philo->table->time_to_sleep * 1000);
}

void    take_forks(t_philosopher *philo)
{
    if (philo->id % 2)
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