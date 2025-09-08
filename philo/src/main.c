/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:09:15 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/03 18:14:00 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int ac, char **av)
{
	t_philosopher philosophers[256];
	t_data input;

	if (!parse(&input, ac, av) || input.max_meal_count == 0)
		return (-1 * input.max_meal_count != 0);

	return (0);
}
