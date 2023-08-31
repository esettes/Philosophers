/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:45:28 by iostancu          #+#    #+#             */
/*   Updated: 2023/08/31 20:25:58 by iostancu         ###   ########.fr       */
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

struct	s_data;

/**
 * @brief eat --> sleep --> think
 * 
 */
typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				thread_id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	size_t			is_eating;
	size_t			is_thinking;
	size_t			is_sleeping;
}				t_philo;

typedef struct s_data
{
	t_philo		*philo;
	useconds_t	t_to_die;
	useconds_t	t_to_eat;
	useconds_t	t_to_sleep;
	useconds_t	many_times_to_eat;
}				t_data;

#endif