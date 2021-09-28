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

void rev_info_nbrs(t_info *info);
{
	if (info[0]->n_philo == 0 || info[0]->t_die == 0 || \
		info[0]->t_eat == 0 || info[0]->t_sleep == 0 || \
		info[0]->n_eats == 0 )
	{
		free(info);
		ft_error();
	}
	if (info[0]->n_philos > MX_PHIL)
	{
		free(info);
		ft_error();
	}
}

t_info *create_info_table(char **argv)
{
	t_info *info;
	int	i;
	
	i = 1;
	info = malloc(sizeof(t_info));
	if (!info)
		ft_error2();
	info[0].n_philo = ft_atoi(argv[i])
	i++;
	info[0].t_die = ft_atoi(argv[i])
	i++;
	info[0].t_eat = ft_atoi(argv[i])
	i++;
	info[0].t_sleep = ft_atoi(argv[i])
	i++;
	if (argv[i])
		info[0].n_eats = ft_atoi(argv[i])
	else
		info[0].n_eats = -1;
	rev_info_nbrs(info);
	initialize_forks_array(info); //////////////////////////// me he quedado aquí
	return(info);
}

int main(int argc, char **argv)
{
	t_info *info;
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
		info = create_info_table(argv);
	}
}