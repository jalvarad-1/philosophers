/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finisher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:25:16 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/20 15:26:32 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_alive(t_philo *ph)
{
	if (ft_get_time() > ph->last_eat + ph->prg->t_die)
	{
		print_actions(ph, "(%lu) Philosopher %d died.\n");
		ph->prg->somebody_is_die = 1;
		return (0);
	}
	return (1);
}

static void	join_and_destroy(t_philo *ph, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(ph[i].t_ph, NULL);
		i++;
	}
	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_destroy(&ph[0].m_f[i]);
		i++;
	}
	pthread_mutex_destroy(&ph[0].prg->m_print);
	free(ph[0].m_f);
	free(ph[0].prg);
	free(ph);
}

void	finisher_checker(t_philo *ph, int n_philos)
{
	int	i;
	int	complete_eats;

	while (!ph->prg->somebody_is_die)
	{
		i = 0;
		complete_eats = 0;
		while (i < n_philos)
		{
			if (!is_alive(&ph[i]))
				break ;
			if (ph[i].full)
			{
				complete_eats++;
				if (complete_eats == ph->prg->n_philo)
				{
					ph->prg->somebody_is_die = 1;
					break ;
				}
			}
			i++;
		}
	}
	join_and_destroy(ph, n_philos);
}
