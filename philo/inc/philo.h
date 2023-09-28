/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:45:28 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/28 22:14:22 by iostancu         ###   ########.fr       */
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

# define FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DIE		"died"
# define ALLOC_ERR	"Allocation error"

struct	s_data;

/**
 * eat --> sleep --> think
 */
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		*tid;
	int				id;
	u_int64_t		start_eating;
	size_t			r_fork;
	size_t			l_fork;
	size_t			times_eaten;
	size_t			is_die;
}				t_philo;

typedef struct s_data
{
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mut_write;
	pthread_mutex_t	*mut_eat;
	pthread_t		controller;
	int				num_philos;
	uint64_t		start_time;
	u_int64_t		t_to_die;
	u_int64_t		t_to_eat;
	u_int64_t		t_to_sleep;
	u_int64_t		many_times_to_eat;
}				t_data;

void		ft_putendlc_fd(char *color, char *s, int fd);
void		ft_putstrc_fd(char *color, char *s, int fd);

char		*ft_itoa(u_int64_t n);
u_int64_t	ft_atoi(const char *str);

u_int64_t	get_time(void);
int			f_usleep(u_int64_t time);
void		print_status(int id, t_data *data, char *act, char *col);

int			init_data(t_data **data, int n_philos, u_int64_t t_sleep, u_int64_t t_eat,
						u_int64_t t_die, int many_times_to_eat);
int			init_philos(t_data *data);
void		*ft_exit(t_data *data);

void		p_sleep(t_philo *ph);
void		p_eat(t_philo *ph);
void		p_think(t_philo *ph);

#endif
