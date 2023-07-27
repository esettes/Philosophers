/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:45:28 by iostancu          #+#    #+#             */
/*   Updated: 2023/07/28 00:02:07 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_state
{
}				t_state;

typedef struct s_philo
{
	int			id;
	useconds_t	t_to_die;
	useconds_t	t_to_eat;
	useconds_t	t_to_sleep;
	int			many_times_to_eat;
}				t_philo;

typedef struct s_simulation
{
	t_philo		*philos;
}				t_simulation;

#endif