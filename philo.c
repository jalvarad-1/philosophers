/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:21 by jalvarad          #+#    #+#             */
/*   Updated: 2021/10/03 17:05:08 by jalvarad         ###   ########.fr       */
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
		thinkers[i].l_fork = &m_forks[i - 1];
		thinkers[i].l_fork = &m_forks[i];
		thinkers[i].prg = info;
		i++;
	}
}
/*Esta funcion solo sirve para hacer pruebas basicas sobre los hilos,
posiblemente la quitaré*/
void	*hunger_games(void *th)
{
	t_philo	*ph;

	ph = (t_philo *)th;
	printf("lock -> %d\n",pthread_mutex_lock(&ph->prg->m_prnt));
	printf("puta %d\n", ph->n_id);
	printf("unlock -> %d\n",pthread_mutex_unlock(&ph->prg->m_prnt));
	if (ph.prg->n_philo == 1)
		ft_error2();      ////////////////////liberar todo lo previamente reservado
	else if (ph.prg->n_philo%2 == 0)
	{
		if (ph.n_id%2 == 0)
		{
			go_routine(ph);
		}
		else if (ph.n_id%2 == 1)
		{
			go_think(ph);
		}
	}
	else if (ph.prg->n_philo%2 == 1)
	{

	}
	if (ph->n_id == 1)
	{
		pthread_mutex_lock(ph->l_fork);
		ph->prg->forks[ph->prg->n_philo - 1] = 1;
		ph->status = 7;
		pthread_mutex_unlock(ph->l_fork);
	}
	else
	{
		pthread_mutex_lock(ph->l_fork);
		ph->prg->forks[ph->n_id - 2] = 1;
		pthread_mutex_unlock(ph->l_fork);
	}
	return (0);
}

/* Dado que hacer una funcion que valorara hilo por hilo si cumple las
variables mas basicas condicionales del programa (si el n_philos es par o
impar) es muy ineficiente he creado dos funciones para los 2 posibles casos, y
en el los condicionales del bucle ya valoro si se puede entrar o no en el bucle
con la funcion adecuada */

void	*even_routine(void *th)
{
	t_philo	*ph;

	ph = (t_philo *)th;
}

void	*odd_routine(void *th)
{
	t_philo	*ph;

	ph = (t_philo *)th;
}

void	init_all_the_program(t_info *info)
{
	t_philo 		*thinkers;
	pthread_mutex_t *m_forks;
	int				i;

	thinkers = malloc(sizeof(t_philo) * info->n_philo);
	m_forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!thinkers || !m_forks)
		ft_error2();
	init_m_forks(info, thinkers, m_forks);
	i = 0;
	printf("mutex creado %d\n", pthread_mutex_init(&info->m_prnt, NULL));
	while (info->n_philo%2 == 0 && i < info->n_philo)
	{
		pthread_create(&thinkers[i].t_ph, NULL, hunger_games, &thinkers[i]);
		usleep(50);
		i++;
	}
	while (info->n_philo%2 == 1 && i < info->n_philo)
	{
		pthread_create(&thinkers[i].t_ph, NULL, hunger_games, &thinkers[i]);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < info->n_philo)
	{
		pthread_join(thinkers[i].t_ph, NULL);
		i++;
	}
	printf("prueba 2:   -> thinker1 %d\n", thinkers[0].status);
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
		i = 0;
		while (i < info->n_philo)
		{
			printf("%d\n", info->forks[i]);
			i++;
		}
	}
	printf("prueba : %d, %d\n", 5%2, 102%2);
}