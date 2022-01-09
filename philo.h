/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:25 by jalvarad          #+#    #+#             */
/*   Updated: 2022/01/09 12:54:08 by jalvarad         ###   ########.fr       */
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
# define RED "\x1b[31m"
# define YELLOW ""
typedef struct s_info
{
    int n_philo;
    int somebody_is_die;
    int t_die;
    int t_eat;
	int t_sleep;
    int n_eats;
    int die;
    int *forks; //// nbr de tenedores     1 = está ocupado   0 = está libre
    pthread_mutex_t	m_print; /// mutex to print
}	t_info;

typedef struct s_philo
{
    int status;   ///// 0 = coge un tenedor --- 1 = está comiendo
    int n_id;     ///// 2 = ha acabado de comer --- 3 = duerme    
    int eat_counts;
    long int time_init;///// 4 = debe pensar  ---- 5 = tiene fork izquierdo
    long int time_now;
    long int last_eat;
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
long int     ft_get_time();
void ft_usleep(long int max_time);

/////// PRINTS /////////
void	print_takefork(t_philo *ph);
void	print_eat(t_philo *ph);
void	print_sleep(t_philo *ph);
void	print_think(t_philo *ph);
void	print_die(t_philo *ph);
#endif