/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_others.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:51:28 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/24 14:59:29 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_actions(t_philo *ph, char *action)
{
	long int	now;

	pthread_mutex_lock(&ph->prg->m_print);
	now = ft_get_time() - ph->time_init;
	if (!ph->prg->somebody_is_die)
		printf(action, now, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_print);
}

void	*init_check(void *th)
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)th;
	ph->prg->open = 0;
	while (!ph->prg->open)
	{
		i = 1;
		while (i < ph->prg->n_philo)
		{
			if (!ph[i].yes)
				break ;
			if (i == ph->prg->n_philo - 1 || i == ph->prg->n_philo - 2)
			{
				ph->prg->open = 1;
			}
			i += 2;
		}
	}
	return (NULL);
}

void	aux_init(t_info *info, t_philo *thinkers, pthread_mutex_t *m_forks)
{
	int	i;

	i = 1;
	while (i < info->n_philo)
	{
		if (thinkers[i].n_id % 2)
		{
			thinkers[i].l_fork = &m_forks[thinkers[i].n_id - 2];
			thinkers[i].r_fork = &m_forks[thinkers[i].n_id - 1];
		}
		if (!(thinkers[i].n_id % 2))
		{
			thinkers[i].r_fork = &m_forks[thinkers[i].n_id - 2];
			thinkers[i].l_fork = &m_forks[thinkers[i].n_id - 1];
		}
		thinkers[i].prg = info;
		thinkers[i].eat_counts = 0;
		thinkers[i].yes = 0;
		i++;
	}
}
