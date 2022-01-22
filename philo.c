/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:21 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/21 12:29:30 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_m_forks(t_info *info, t_philo *thinkers, pthread_mutex_t *m_forks)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		thinkers[i].n_id = i + 1;
		thinkers[i].m_f = m_forks;
		pthread_mutex_init(&m_forks[i], NULL);
		i++;
	}
	i = 0;
	thinkers[i].l_fork = &m_forks[info->n_philo - 1];
	thinkers[i].r_fork = &m_forks[i];
	thinkers[i].prg = info;
	thinkers[i].eat_counts = 0;
	thinkers[i].yes = 0;
	i++;
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
		;
	while (ph->full == 0 &&!ph->prg->somebody_is_die)
	{
		to_do_list(ph);
	}
	return (NULL);
}

void	*init_check(void *th)
{
	t_philo	*ph;
	int i;

	ph = (t_philo *)th;
	ph->prg->open = 0;
	// esta función se va a encargar de revisar que en el primer turno de comida todos los filosofos esten comiendo
	while (!ph->prg->open)
	{
		i = 1;
		while (i < ph->prg->n_philo)
		{
			if (!ph[i].yes)
				break ;
			if (i == ph->prg->n_philo - 1)
			{
				ph->prg->open = 1;
				printf("holoa \n");
			}
			i += 2;
		}
	}
	return (NULL);
}

void	init_all_the_program(t_info *info)
{
	t_philo			*thinkers;
	pthread_t		det;
	pthread_mutex_t	*m_forks;
	int				i;
	long int		init;

	thinkers = malloc(sizeof(t_philo) * info->n_philo );
	m_forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!thinkers || !m_forks)
		ft_error2();
	init_m_forks(info, thinkers, m_forks);
	i = 0;
	init = ft_get_time();
	pthread_create(&det, NULL, init_check, thinkers);
	while (i < info->n_philo)
	{
		thinkers[i].time_init = init;
		thinkers[i].last_eat = thinkers[i].time_init;
		pthread_create(&thinkers[i].t_ph, NULL, ph_routine, &thinkers[i]);
		i++;
	}
	finisher_checker(thinkers, info->n_philo);
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
}
