/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:16:27 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 05:50:33 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_semaphores(t_data *data)
{
	int	c;

	c = data->philosopher_count;
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_ROOM_NAME);
	sem_unlink(SEM_DEATH_NAME);
	data->forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0644, c);
	if (data->forks == SEM_FAILED)
		return (-1);
	data->write = sem_open(SEM_WRITE_NAME, O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED)
		return (-1);
	data->room = sem_open(SEM_ROOM_NAME, O_CREAT, 0644, c - 1);
	if (data->room == SEM_FAILED)
		return (-1);
	data->death = sem_open(SEM_DEATH_NAME, O_CREAT, 0644, 1);
	if (data->death == SEM_FAILED)
		return (-1);
	return (0);
}

void	cleanup_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->write);
	sem_close(data->room);
	sem_close(data->death);
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_ROOM_NAME);
	sem_unlink(SEM_DEATH_NAME);
}

void	close_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->write);
	sem_close(data->room);
	sem_close(data->death);
}
