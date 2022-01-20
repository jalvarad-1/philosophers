/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:51:28 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/20 13:26:40 by jalvarad         ###   ########.fr       */
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
