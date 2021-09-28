#include "philo.h"

void ft_error(void)
{
	ft_putstr_fd("Philosophers usage: \n\n", 1);
	ft_putstr_fd("You have to pass 4 or 5 five arguments to this program \n\n", 1);
	ft_putstr_fd("[philosophers_numbers] [time_to_die] [time_to_eat] [time_to_sleep] \n\n", 1);
	ft_putstr_fd("and an optional 5th argument -->  [number_of_times_each_philosopher_should_eat]\n\n", 1);
	exit(-1);
}

void ft_error2(void)
{
	printf("Ups!!! An error has ocurred.\n");
	exit(-1);
}