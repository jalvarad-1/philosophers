/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:26:25 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/26 16:38:19 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# define MX_PHIL 200
typedef struct s_info
{
	int n_philo;
    int t_die;
    int t_eat;
	int t_sleep;
    int n_eats;
    int *forks; //// nbr de tenedores     1 = está ocupado   0 = está libre
    pthread_mutex_t	m_prnt; /// mutex to print
}	t_info;

typedef struct s_philo
{
    int status;
    int n_id;
    int l_fork;
    int r_fork;
    t_info *prg;
    pthread_mutex_t *m_f;
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
#endif