/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:16:27 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/04 18:44:27 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_semaphores(t_data *data)
{
	int c;

	c = data->philosopher_count;
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_ROOM_NAME);
	data->forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0644, c);
	data->write = sem_open(SEM_WRITE_NAME, O_CREAT, 0644, 1);
	data->room = sem_open(SEM_ROOM_NAME, O_CREAT, 0644, c - 1);
}