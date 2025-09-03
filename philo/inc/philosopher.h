/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:12:52 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/03 11:55:45 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "error.h"
# include <unistd.h>

/**
 * t_data - input data structure
 *
 * @philosopher_count: number of philosophers
 * @time_to_die: time that causes a philosopher to die if hasn't eaten
 * @time_to_eat: time it takes to eat
 * @time_to_sleep: time it takes to sleep
 * @max_meal_count: Optional input of max meals to stop the program.
 */
typedef struct s_data
{
	int	philosopher_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meal_count;
}		t_data;

typedef struct s_philosopher
{
	int	id;
	int	meal_count;
	int	last_meal_time;
}		t_philosopher;

int		parse(t_data *arg, int argc, char **argv);

// Utils
void	ft_putstr_fd(char *s, int fd);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_atoi(const char *str);
int		check_int_overflow(char *str);
int		check_num(char *str);

#endif /* PHILOSPHER_H */
