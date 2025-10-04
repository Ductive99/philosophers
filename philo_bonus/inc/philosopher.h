/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:17:12 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/04 18:47:17 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "error.h"
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include "semaphore.h"

typedef struct  s_data
{
    int							philosopher_count;
	uint64_t					simulation_start_time;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							max_meal_count;
	int							simulation_over;
	sem_t						forks;
	sem_t						room;
	sem_t						write;
}   t_data;

int	parse(t_data *arg, int argc, char **argv);

#endif /* PHILOSOPHER_H */
