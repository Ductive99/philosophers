/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:31:18 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/09 05:39:11 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <signal.h>

int	kill_all_processes(pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGINT);
		i++;
	}
	return (0);
}

int	cleanup_and_exit(t_data *data, int exit_code)
{
	cleanup_semaphores(data);
	return (exit_code);
}
