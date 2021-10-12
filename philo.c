/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:21 by jalvarad          #+#    #+#             */
/*   Updated: 2021/10/12 18:45:05 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rev_info_nbrs(t_info *info)
{
	if (info[0].n_philo == 0 || info[0].t_die == 0 || \
		info[0].t_eat == 0 || info[0].t_sleep == 0 || \
		info[0].n_eats == 0 )
	{
		free(info);
		ft_error();
	}
	if (info[0].n_philo > MX_PHIL)
	{
		free(info);
		ft_error();
	}
}

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

t_info	*create_info_table(char **argv)
{
	t_info	*info;
	int		i;

	i = 1;
	info = malloc(sizeof(t_info));
	if (!info)
		ft_error2();
	info[0].n_philo = ft_atoi(argv[i]);
	i++;
	info[0].t_die = ft_atoi(argv[i]);
	i++;
	info[0].t_eat = ft_atoi(argv[i]);
	i++;
	info[0].t_sleep = ft_atoi(argv[i]);
	i++;
	if (argv[i])
		info[0].n_eats = ft_atoi(argv[i]);
	else
		info[0].n_eats = -1;
	rev_info_nbrs(info);
	info[0].somebody_is_die = 0;
	info[0].forks = initialize_forks_array(info[0].n_philo);
	return (info);
}

/*////3 -- 310 -- 100 -- 100
T->eat + t->sleep < t die
Pares T eat > t die /  2
impare t eat > t_die / 3 
*/

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
	i++;
	while (i < info->n_philo)
	{
		thinkers[i].l_fork = &m_forks[thinkers[i].n_id - 2];
		thinkers[i].r_fork = &m_forks[thinkers[i].n_id - 1];
		thinkers[i].prg = info;
		i++;
	}
}

/*Esta funcion solo sirve para hacer pruebas basicas sobre los hilos,
posiblemente la quitaré*/

void	routine_aux(t_philo *ph)
{
	print_eat(ph);
	ft_usleep((ph->time_now + ph->prg->t_eat));
	if (ph->n_id == 1)
	{
		ph->prg->forks[ph->prg->n_philo - 1] = 0;
		ph->prg->forks[0] = 0;
	}
	else
	{
		ph->prg->forks[ph->n_id - 2] = 0;
		ph->prg->forks[ph->n_id - 1] = 0;
	}
	ph->status = 2;
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

void	ph_sleep(t_philo *ph)
{
	print_sleep(ph);
	ft_usleep((ph->time_now + ph->prg->t_sleep));
	ph->status = 4;
}

void	rev_forks(t_philo *ph)
{
	if (ph->status == 1)
	{
		while (pthread_mutex_lock(ph->r_fork) != 0)
			;
		if (ph->n_id != 1)
			ph->prg->forks[ph->n_id - 1] = 1;
		if (ph->n_id == 1)
			ph->prg->forks[0] = 1;
		if (ph->prg->forks[ph->n_id - 2] == 1 && \
			ph->prg->forks[ph->n_id - 1] == 1)
		{
			routine_aux(ph);
			ph_sleep(ph);
		}
	}
	else if (ph->status == 5)
	{
		while (pthread_mutex_lock(ph->l_fork) != 0)
			;
		if (ph->n_id != 1)
			ph->prg->forks[ph->n_id - 2] = 1;
		if (ph->n_id == 1)
			ph->prg->forks[ph->prg->n_philo - 1] = 1;
		if (ph->prg->forks[ph->n_id - 2] == 1 && \
			ph->prg->forks[ph->n_id - 1] == 1)
		{
			routine_aux(ph);
			ph_sleep(ph);
		}
	}
}
void	routine(t_philo *ph)
{
	while (1)
	{
		//rev_forks(ph);
		/*if(ph->status == 0 && ph->n_id == 1)
		{
			pthread_mutex_lock(ph->l_fork);
			ph->prg->forks[ph->prg->n_philo - 1] = 1;
			ph->status = 1;
			print_takefork(ph);
			while (ph->status == 1 && pthread_mutex_lock(ph->r_fork) != 0)
				;
			//pthread_mutex_lock(ph->r_fork);
			if (ph->status == 1)
			{
				ph->status = 5;
				ph->prg->forks[0] = 1;
				print_takefork(ph);
			}
			if (ph->prg->forks[ph->prg->n_philo - 1] == 1 && \
				ph->prg->forks[0] == 1)
			{
				routine_aux(ph);
				ph_sleep(ph);
			}
			if (ph->status == 0)
				ph->status = 4;
		}*/
		if (ph->status == 0 && ph->n_id % 2 == 0)
		{
			pthread_mutex_lock(ph->r_fork);
			ph->prg->forks[ph->n_id - 1] = 1;
			ph->status = 5;
			print_takefork(ph);
			pthread_mutex_lock(ph->l_fork);
			ph->status = 1;
			ph->prg->forks[ph->n_id - 2] = 1;
			print_takefork(ph);
			if (ph->prg->forks[ph->n_id - 2] == 1 && \
				ph->prg->forks[ph->n_id - 1] == 1)
			{
				routine_aux(ph);
				ph_sleep(ph);
			}
			if (ph->status == 0)
				ph->status = 4;
		}
		else if (ph->status == 0 && ph->n_id %2 == 1)///// estoy por aquí
		{
			pthread_mutex_lock(ph->l_fork);
			ph->prg->forks[ph->n_id - 2] = 1;
			ph->status = 1;
			print_takefork(ph);
			pthread_mutex_lock(ph->r_fork);
			ph->prg->forks[ph->n_id - 1] = 1;
			ph->status = 5;
			print_takefork(ph);
			if (ph->prg->forks[ph->n_id - 2] == 1 && \
				ph->prg->forks[ph->n_id - 1] == 1)
			{
				routine_aux(ph);
				ph_sleep(ph);
			}
		}
		else if(ph->status == 0 && ph->n_id == 1)
		{
			pthread_mutex_lock(ph->l_fork);
			ph->prg->forks[ph->prg->n_philo - 1] = 1;
			ph->status = 1;
			print_takefork(ph);
			pthread_mutex_lock(ph->r_fork);
			ph->status = 5;
			ph->prg->forks[0] = 1;
			print_takefork(ph);
			if (ph->prg->forks[ph->prg->n_philo - 1] == 1 && \
				ph->prg->forks[0] == 1)
			{
				routine_aux(ph);
				ph_sleep(ph);
			}
			if (ph->status == 0)
				ph->status = 4;
		}
		else if (ph->status == 4)
		{
			ph->status = 0;
			print_think(ph);
			usleep((ph->prg->t_die/6) * 1000);
		}
	}
}

/* Dado que hacer una funcion que valorara hilo por hilo si cumple las
variables mas basicas condicionales del programa (si el n_philos es par o
impar) es muy ineficiente he creado dos funciones para los 2 posibles casos, y
en el los condicionales del bucle ya valoro si se puede entrar o no en el bucle
con la funcion adecuada */

void	*nph_evenroutine(void *th)
{
	t_philo	*ph;

	ph = (t_philo *)th;
	if (ph->n_id%2 == 0)
	{
		routine(ph);
	}
	else
	{
		usleep(100);
		routine(ph);
	}
	return (0);
}

int rev_all_thinkers(t_philo *thinkers, t_info *info, int a)
{
	int i;

	i = 0;
	while (i < info->n_philo)
	{
		if (thinkers[i].n_id%2 == a && thinkers[i].status != 1)
			break ;
		i++;
	}
	if (i == info->n_philo)
		return (1);
	else
		return (0);

}

void	init_all_the_program(t_info *info)
{
	t_philo 		*thinkers;
	pthread_mutex_t *m_forks;
	int				i;
//	int				a;

	thinkers = malloc(sizeof(t_philo) * info->n_philo);
	m_forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!thinkers || !m_forks)
		ft_error2();
	init_m_forks(info, thinkers, m_forks);
	i = 0;
//	a = ft_get_time();
	while (i < info->n_philo)
	{
		thinkers[i].time_init = ft_get_time();
		thinkers[i].last_eat = thinkers[i].time_init;
		thinkers[i].status = 0;
		pthread_create(&thinkers[i].t_ph, NULL, nph_evenroutine, &thinkers[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < info->n_philo)
	{
		pthread_join(thinkers[i].t_ph, NULL);
		i++;
	}
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
		init_all_the_program(info);
	}
}