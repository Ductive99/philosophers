/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:12:52 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/19 03:28:30 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "error.h"
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 256

typedef struct s_philosopher	t_philosopher;
typedef struct s_data			t_data;

struct							s_philosopher
{
	int							id;
	int							meal_count;
	uint64_t					last_meal_time;
	pthread_t					thread;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	t_data						*table;
};

/**
 * t_data - input data structure
 *
 * @philosopher_count: number of philosophers
 * @time_to_die: time that causes a philosopher to die if hasn't eaten
 * @time_to_eat: time it takes to eat
 * @time_to_sleep: time it takes to sleep
 * @max_meal_count: Optional input of max meals to stop the program.
 * @philos: array of philosopher data structure
 * @print_mutex: mutex to handle printing philosopher status
 */
struct							s_data
{
	int							philosopher_count;
	uint64_t					simulation_start_time;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							max_meal_count;
	t_philosopher				philos[MAX_PHILOS];
	pthread_mutex_t				forks[MAX_PHILOS];
	pthread_t					waiter;
	pthread_mutex_t				print_mutex;
};

typedef enum e_status
{
	DIED = 0,
	THINKING = 1,
	TAKING_FORK = 2,
	EATING = 3,
	SLEEPING = 4,
}								t_status;

void							*philosopher_routine(void *arg);
void							*waiter_routine(void *arg);

void							print_status(t_data *data, int philo_id,
									t_status status);

int								parse(t_data *arg, int argc, char **argv);

// Utils
char							*ft_strncpy(char *dest, const char *src,
									size_t n);
void							ft_putstr_fd(char *s, int fd);

int								check_int_overflow(char *str);
int								ft_atoi(const char *str);
int								check_num(char *str);

uint64_t						get_time_in_ms(void);

#endif /* PHILOSPHER_H */
