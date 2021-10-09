/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:51:28 by jalvarad          #+#    #+#             */
/*   Updated: 2021/10/09 15:12:10 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_takefork(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_f);
	printf("(%d) Philosopher %d has taken a fork\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_f);
}

void	print_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_e);
	printf("(%d) Philosopher %d is eating\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_e);
}

void	print_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_s);
	printf("(%d) Philosopher %d is sleeping\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_s);
}

void	print_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_t);
	printf("(%d) Philosopher %d is thinking\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_t);
}

void	print_die(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_d);
	printf("(%d) Philosopher %d died\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_d);
}
