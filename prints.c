/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:51:28 by jalvarad          #+#    #+#             */
/*   Updated: 2021/10/10 15:23:37 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_takefork(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_f);
	ph->time_now = ft_get_time();
	printf("(%d) Philosopher %d has taken a fork\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_f);
}

void	print_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_e);
	ph->time_now = ft_get_time();
	printf("(%d) Philosopher %d is eating\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_e);
}

void	print_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_s);
	ph->time_now = ft_get_time();
	printf("(%d) Philosopher %d is sleeping\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_s);
}

void	print_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_t);
	ph->time_now = ft_get_time();
	printf("(%d) Philosopher %d is thinking\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_t);
}

void	print_die(t_philo *ph)
{
	pthread_mutex_lock(&ph->prg->m_prnt_d);
	ph->time_now = ft_get_time();
	printf("(%d) Philosopher %d died\n", ph->time_now - ph->time_init, ph->n_id);
	pthread_mutex_unlock(&ph->prg->m_prnt_d);
}
