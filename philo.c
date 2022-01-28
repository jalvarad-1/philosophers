/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:21 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/28 09:33:49 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_m_forks(t_info *info, t_philo *thinkers, pthread_mutex_t *m_f)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		thinkers[i].n_id = i + 1;
		thinkers[i].m_f = m_f;
		pthread_mutex_init(&m_f[i], NULL);
		i++;
	}
	i = 0;
	thinkers[i].l_fork = &m_f[info->n_philo - 1];
	thinkers[i].r_fork = &m_f[i];
	thinkers[i].prg = info;
	thinkers[i].eat_counts = 0;
	thinkers[i].yes = 0;
	aux_init(info, thinkers, m_f);
	pthread_mutex_init(&info->m_print, NULL);
}

void	to_do_list(t_philo *ph)
{
	pthread_mutex_lock(ph->r_fork);
	print_actions(ph, "(%lu) Philosopher %d has taken a fork.\n");
	pthread_mutex_lock(ph->l_fork);
	print_actions(ph, "(%lu) Philosopher %d has taken a fork.\n");
	ph->yes = 1;
	print_actions(ph, "(%lu) Philosopher %d is eating.\n");
	ph->last_eat = ft_get_time();
	ft_usleep(ph->prg->t_eat);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
	ph->eat_counts++;
	if (ph->eat_counts == ph->prg->n_eats)
	{
		ph->full = 1;
		return ;
	}
	print_actions(ph, "(%lu) Philosopher %d is sleeping.\n");
	ft_usleep(ph->prg->t_sleep);
	print_actions(ph, "(%lu) Philosopher %d is thinking.\n");
	if (ph->prg->n_philo % 2)
		usleep(100);
}

void	*ph_routine(void *th)
{
	t_philo	*ph;

	ph = (t_philo *)th;
	ph->full = 0;
	if (ph->prg->n_philo == 1)
	{
		pthread_mutex_lock(&ph->m_f[0]);
		printf("(0) Philosopher 1 has taken a fork.\n");
		ft_usleep(ph->prg->t_die);
		printf("(%d) Philosopher 1 died.\n", ph->prg->t_die + 1);
		ph->prg->somebody_is_die = 1;
		pthread_mutex_unlock(&ph->m_f[0]);
		return (NULL);
	}
	while (ph->n_id % 2 && !ph->prg->open)
		usleep(100);
	if (ph->prg->n_philo % 2 && ph->n_id == ph->prg->n_philo - 1)
		usleep(100);
	while (ph->full == 0 &&!ph->prg->somebody_is_die)
		to_do_list(ph);
	return (NULL);
}

void	init_all_the_program(t_info *info)
{
	t_philo			*thinkers;
	pthread_t		det;
	pthread_mutex_t	*m_forks;
	int				i;
	long int		init;

	thinkers = malloc(sizeof(t_philo) * info->n_philo);
	m_forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!thinkers || !m_forks)
		ft_error2();
	init_m_forks(info, thinkers, m_forks);
	i = 0;
	init = ft_get_time();
	if (info->n_philo < 1)
		pthread_create(&det, NULL, init_check, thinkers);
	while (i < info->n_philo)
	{
		thinkers[i].time_init = init;
		thinkers[i].last_eat = thinkers[i].time_init;
		pthread_create(&thinkers[i].t_ph, NULL, ph_routine, &thinkers[i]);
		i++;
	}
	finisher_checker(det, thinkers, info->n_philo);
}

int	main(int argc, char **argv)
{
	t_info	*info;
	int		i;

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
		init_all_the_program(info);
	}
	system("leaks philo");
}
