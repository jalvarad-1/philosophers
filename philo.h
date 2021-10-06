/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:25 by jalvarad          #+#    #+#             */
/*   Updated: 2021/10/06 16:40:47 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# define MX_PHIL 200
typedef struct s_info
{
    int n_philo;
    int t_die;
    int t_eat;
	int t_sleep;
    int n_eats;
    int *forks; //// nbr de tenedores     1 = está ocupado   0 = está libre
    pthread_mutex_t	m_prnt_f; /// mutex to print
    pthread_mutex_t	m_prnt_e;
    pthread_mutex_t	m_prnt_s;
    pthread_mutex_t	m_prnt_t;
    pthread_mutex_t	m_prnt_d;
}	t_info;

typedef struct s_philo
{
    int status;
    int n_id;
    int time;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_info *prg;
    pthread_mutex_t *m_f;
    pthread_t   t_ph;
}   t_philo;

/*///////////PARSER_UTILS */
int	ft_str_is_numeric(char *str);

//////////  ERROR_MANAGEMENT ////////////////
void	ft_error(void);
void    ft_error2(void);

////////   PHILO /////////


//////// UTILS /////////
void    ft_putstr_fd(char *s, int fd);
int     ft_atoi(const char *str);
int     ft_isdigt(int c);
int	ft_get_time();
#endif