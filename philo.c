/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:21 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/26 16:47:39 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_error(void)
{
	ft_putstr_fd("Philosophers usage: \n\n", 1);
	ft_putstr_fd("You have to pass 4 or 5 five arguments to this program \n\n", 1);
	ft_putstr_fd("[philosophers_numbers] [time_to_die] [time_to_eat] [time_to_sleep] \n\n", 1);
	ft_putstr_fd("and an optional 5th argument -->  [number_of_times_each_philosopher_should_eat]\n\n", 1);
	exit(-1);
}

int	ft_str_is_numeric(char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (str[a] != '\0')
	{
		if (str[0] == '+')
			a++;
		if (str[a] >= '0' && str[a] <= '9')
			b = b * 1;
		if (str[a] < '0' || str[a] > '9')
			b = 0;
		a++;
	}
	return (b);
}

int main(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
		ft_error();
	else
	{
		while (argv[i])
		{
			if (ft_str_is_numeric(argv[i]) != 1)
				ft_error();
			i++;
		}
	}
}