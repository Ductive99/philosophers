/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:17:12 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 05:10:53 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "error.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEM_FORKS_NAME "/philo_forks"
#define SEM_WRITE_NAME "/philo_write"
#define SEM_DEATH_NAME "/philo_dead"
#define SEM_ROOM_NAME "/philo_room"
#define MAX_PHILOS 256

typedef struct s_data
{
	int philosopher_count;
	uint64_t simulation_start_time;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meal_count;
	sem_t *death;
	sem_t *forks;
	sem_t *room;
	sem_t *write;
} t_data;

typedef struct s_philo
{
	int id;
	t_data *table;
	int meal_count;
	uint64_t last_meal_time;
} t_philo;

int parse(t_data *arg, int argc, char **argv);

uint64_t get_time_in_ms(void);
void ft_usleep(int time_in_ms);
int ft_usleep_with_death_check(t_philo *philo, int time_in_ms);

void philosopher_routine(t_data *data, int id);
void supervisor_routine(t_data *data, pid_t *pids);
int should_die(t_philo *philo);
void die_and_exit(t_philo *philo);
void *monitor_death(void *arg);

int kill_all_processes(pid_t *pids, int count);
int cleanup_and_exit(t_data *data, int exit_code);

void print_status(t_philo *philo, char *status);

int init_semaphores(t_data *data);
void cleanup_semaphores(t_data *data);
void close_semaphores(t_data *data);

char *ft_strncpy(char *dest, const char *src, size_t n);
void ft_putstr_fd(char *s, int fd);
int check_int_overflow(char *str);
int ft_atoi(const char *str);
int check_num(char *str);

#endif /* PHILOSOPHER_H */
