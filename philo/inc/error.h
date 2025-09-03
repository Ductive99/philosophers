/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 08:35:17 by esouhail          #+#    #+#             */
/*   Updated: 2025/09/03 10:51:08 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum {
    ERR_ARGC = 0,
    ERR_INVALID_NUMBER = 1,
    ERR_INT_OVERFLOW = 2,
    ERR_NEGATIVE_NUMBER = 3,
    ERR_PHILO_COUNT = 4,
}   error_code;

int	print_error(error_code code, char *str);

#endif /* ERROR_H */
