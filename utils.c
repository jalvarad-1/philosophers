/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:39 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/09 11:47:31 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			sg;
	long long	num;

	sg = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str != '+' && *str != '-' && ft_isdigit((int)*str) == 0)
		return (0);
	if (*str == '-')
		sg = -1;
	if (ft_isdigit((int)*str) == 0)
		str++;
	if (ft_isdigit((int)*str) == 0)
		return (0);
	while (ft_isdigit((int)*str))
	{
		num = num * 10 + *str++ - '0';
		if ((num * sg) > INT_MAX)
			return (-1);
		if ((num * sg) < INT_MIN)
			return (0);
	}
	return (num * sg);
}

/*Devuelve el tiempo en milisegundos*/
long int	ft_get_time(void)
{
	struct timeval tp;

	if (gettimeofday(&tp, NULL) == -1)
		ft_error2();
	return((tp.tv_sec * 1000) + tp.tv_usec / 1000);
}

void ft_usleep(long int max_time)
{
	long int	init_time;
	
	init_time = ft_get_time();
	while ((ft_get_time() - init_time) < time)
		usleep(100);
}