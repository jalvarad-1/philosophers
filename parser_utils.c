/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:03:00 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/20 14:45:57 by jalvarad         ###   ########.fr       */
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
