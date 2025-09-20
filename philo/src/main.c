/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:09:15 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/20 16:02:55 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philosopher(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (parse(&data, ac, av) == -1 || data.max_meal_count == 0)
		return (-1 * (data.max_meal_count != 0));
	if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
		return (ft_putstr_fd("Failed to create print mutex\n", 2), 1);
	if (!init_philosopher(&data))
		return (1);
	i = -1;
	pthread_create(&data.waiter, NULL, waiter_routine, &data);
	while (++i < data.philosopher_count)
		pthread_join(data.philos[i].thread, NULL);
	pthread_join(data.waiter, NULL);
	i = -1;
	while (++i < data.philosopher_count)
		pthread_mutex_destroy(&data.forks[i]);
	pthread_mutex_destroy(&data.print_mutex);
	return (0);
}

int	init_philosopher(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philosopher_count)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_putstr_fd("Failed to create fork mutex", 2), 0);
	i = -1;
	data->simulation_start_time = get_time_in_ms();
	while (++i < data->philosopher_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal_time = data->simulation_start_time;
		data->simulation_over = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->philosopher_count];
		data->philos[i].table = data;
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
		{
			ft_putstr_fd("Failed to create philosopher thread", 2);
			return (0);
		}
	}
	return (1);
}
