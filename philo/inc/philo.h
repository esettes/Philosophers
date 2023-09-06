/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:45:28 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/07 00:06:29 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>

# define RED_		"\x1b[31m"
# define GREEN_		"\x1b[32m"
# define YELLOW_	"\x1b[33m"
# define BLUE_		"\x1b[34m"
# define VIOLET_	"\x1b[35m"
# define CYAN_		"\x1b[36m"
# define RESET_		"\x1b[0m"

struct	s_data;

/**
 * @brief eat --> sleep --> think
 * 
 */
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		tid;
	int				id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	size_t			is_eating;
	size_t			is_thinking;
	size_t			is_sleeping;
}				t_philo;

typedef struct s_data
{
	t_philo		*philo;
	int			num_philos;
	int			aux_var;
	useconds_t	t_to_die;
	useconds_t	t_to_eat;
	useconds_t	t_to_sleep;
	useconds_t	many_times_to_eat;
}				t_data;

void	ft_putendlc_fd(char *color, char *s, int fd);
char	*ft_itoa(int n);
int		f_usleep(useconds_t time);

#endif
