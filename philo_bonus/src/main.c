/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:16:14 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/04 18:50:48 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int ac, char **av)
{
    t_data  data;

    // Parsing
    if (parse(&data, ac, av) == -1 || data.max_meal_count == 0)
        return (-1 * (data.max_meal_count != 0));
    
    // Initialize semaphores
    init_semaphores(&data);
    
    // Create Processes

    // Implement Philosopher Routines for Processes

    // Parent Process is a Supervisor
}