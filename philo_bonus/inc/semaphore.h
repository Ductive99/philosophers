/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:14:23 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/04 18:48:15 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORE_H
# define SEMAPHORE_H

# include <semaphore.h>
# include <fcntl.h>

# define SEM_FORKS_NAME "/philo_forks"
# define SEM_WRITE_NAME "/philo_write"
# define SEM_ROOM_NAME  "/philo_room"

int	init_semaphores(t_data *data);

#endif /* SEMAPHORE_H */