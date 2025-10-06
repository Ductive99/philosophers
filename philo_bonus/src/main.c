/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:16:14 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/06 04:16:43 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_data	data;
	pid_t	pids[MAX_PHILOS];
	int		i;

	if (parse(&data, ac, av) == 0 || data.max_meal_count == 0)
		return (1);
	if (init_semaphores(&data) == -1)
		return (cleanup_and_exit(&data, 1));
	data.simulation_start_time = get_time_in_ms();
	i = -1;
	while (++i < data.philosopher_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			kill_all_processes(pids, i);
			return (cleanup_and_exit(&data, 1));
		}
		else if (pids[i] == 0)
		{
			philosopher_routine(&data, i + 1);
			exit(1);
		}
	}
	return (supervisor_routine(&data, pids), 0);
}
