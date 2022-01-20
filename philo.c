/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:21 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/20 14:47:34 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*initialize_forks_array(int n_philo)
{
	int	*forks;
	int	i;

	i = 0;
	forks = malloc(sizeof(int) * n_philo);
	if (!forks)
		return (0);
	while (i < n_philo)
	{
		forks[i] = 0;
		i++;
	}
	return (forks);
}

void	aux_create_info_table(t_info *info, char **argv)
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
	info[0].forks = initialize_forks_array(info[0].n_philo);
	return (info);
}

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
	i++;
	while (i < info->n_philo)
	{
		thinkers[i].l_fork = &m_forks[thinkers[i].n_id - 2];
		thinkers[i].r_fork = &m_forks[thinkers[i].n_id - 1];
		thinkers[i].prg = info;
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
	if (ph->n_id % 2)
		usleep(100);
	while (ph->full == 0 &&!ph->prg->somebody_is_die)
	{
		to_do_list(ph);
	}
	return (NULL);
}

int	is_alive(t_philo *ph)
{
	if (ft_get_time() > ph->last_eat + ph->prg->t_die)
	{
		print_actions(ph, "(%lu) Philosopher %d died.\n");
		ph->prg->somebody_is_die = 1;
		return (0);
	}
	return (1);
}

void	join_and_destroy(t_philo *ph, int n_philos)
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
	free(ph[0].prg->forks);
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

void	init_all_the_program(t_info *info)
{
	t_philo			*thinkers;
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
