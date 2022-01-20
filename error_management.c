/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:03:21 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/20 11:27:05 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	ft_putstr_fd("Philosophers usage: \n\n", 1);
	ft_putstr_fd("You have to pass 4 or 5 five arguments (numbers > 0)", 1);
	ft_putstr_fd("to this program \n\n", 1);
	ft_putstr_fd("[philosophers_numbers] [time_to_die] [time_to_eat]", 1);
	ft_putstr_fd("[time_to_sleep] \n\n", 1);
	ft_putstr_fd("and an optional 5th argument -->  ", 1);
	ft_putstr_fd("[number_of_times_each_philosopher_should_eat]\n\n", 1);
	exit(1);
}

void	ft_error2(void)
{
	printf("Ups!!! An error has ocurred.\n");
	exit(1);
}
