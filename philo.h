/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:25 by jalvarad          #+#    #+#             */
/*   Updated: 2022/02/12 10:21:55 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# define MAX_PH 200

typedef struct s_info
{
	short int		n_philo;
	bool			somebody_is_die;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	bool			open;
	unsigned int	n_eats;
	pthread_mutex_t	m_print;
}	t_info;

typedef struct s_philo
{
	short int		n_id;
	bool		full;
	bool		yes;
	unsigned int	eat_counts;
	long int		time_init;
	long int		time_now;
	long int		last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_info			*prg;
	pthread_mutex_t	*m_f;
	pthread_t		t_ph;
}	t_philo;

///////////PARSER_UTILS /////////////////////
int			ft_str_is_numeric(char *str);
void		rev_info_nbrs(t_info *info);
t_info		*create_info_table(char **argv);

//////////  ERROR_MANAGEMENT ////////////////
void		ft_error(void);
void		ft_error2(void);

////////   PHILO /////////
void		finisher_checker(pthread_t det, t_philo *ph, int n_philos);
void		*init_check(void *th);
void		aux_init(t_info *info, t_philo *thinkers, pthread_mutex_t *m_forks);
//////// UTILS /////////
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
int			ft_isdigt(int c);
long int	ft_get_time(void);
void		ft_usleep(long int max_time);

/////// PRINTS /////////
void		print_actions(t_philo *ph, char *actions);
#endif