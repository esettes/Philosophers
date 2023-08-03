/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:45:28 by iostancu          #+#    #+#             */
/*   Updated: 2023/08/03 22:23:52 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_log
{
}				t_log;

/**
 * @brief eat --> sleep --> think
 * 
 */
typedef struct s_philo
{
	int				id;
	int				thread_id;
	pthread_mutex_t	*fork;
	useconds_t		t_to_die;
	useconds_t		t_to_eat;
	useconds_t		t_to_sleep;
	size_t			many_times_to_eat;
	size_t			is_eating;
	size_t			is_thinking;
	size_t			is_sleeping;
}				t_philo;

typedef struct s_data
{
	t_philo		*philo;
}				t_data;

#endif