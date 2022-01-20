/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:03:00 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/20 15:28:38 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	rev_info_nbrs(t_info *info)
{
	if (info[0].n_philo <= 0 || info[0].t_die <= 0 || \
		info[0].t_eat <= 0 || info[0].t_sleep <= 0 || \
		info[0].n_eats < 0)
	{
		free(info);
		ft_error();
	}
	if (info[0].n_philo > MAX_PH)
	{
		free(info);
		ft_error();
	}
}

static void	aux_create_info_table(t_info *info, char **argv)
{
	int	i;

	i = 1;
	info[0].n_philo = ft_atoi(argv[i]);
	i++;
	info[0].t_die = ft_atoi(argv[i]);
	i++;
	info[0].t_eat = ft_atoi(argv[i]);
	i++;
	info[0].t_sleep = ft_atoi(argv[i]);
}

t_info	*create_info_table(char **argv)
{
	t_info	*info;
	int		i;

	i = 1;
	info = malloc(sizeof(t_info));
	if (!info)
		ft_error2();
	aux_create_info_table(info, argv);
	if (argv[5])
	{
		info[0].n_eats = ft_atoi(argv[5]);
		if (info[0].n_eats == 0)
		{
			free(info);
			ft_error();
		}
	}
	else
		info[0].n_eats = 0;
	rev_info_nbrs(info);
	info[0].somebody_is_die = 0;
	return (info);
}
