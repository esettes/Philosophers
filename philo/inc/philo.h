/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:13:09 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/13 00:48:47 by iostancu         ###   ########.fr       */
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

typedef struct s_philo
{
	struct s_data		*data;
	pthread_t			*tid;
	int					id;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	uint64_t			times_eaten;
	size_t				is_die;
	uint64_t			start_eating;
	pthread_mutex_t		mut;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		controller;
	pthread_mutex_t	mut_write;
	pthread_mutex_t	mut_start;
	int				num_philos;
	uint64_t		start_time;
	uint64_t		t_to_die;
	uint64_t		t_to_eat;
	uint64_t		t_to_sleep;
	uint64_t		many_times_to_eat;
}				t_data;

void		init_forks(t_data *data, pthread_mutex_t **forks);
int			init_data(t_data **data, int philos, u_int64_t sleep, u_int64_t eat,
					u_int64_t die, int times_to_eat);
/**
 * @brief Philo's id start with 1
 * 
 * @param data 
 * @return int 0 if success, 1 if an error occurs wih allocation
 */
int			init_philos(t_data *data);

void	p_eat(t_philo *ph);

uint64_t	ft_atoi(const char *str);
char		*ft_itoa(uint64_t n);

void		ft_putstrc_fd(char *color, char *s, int fd);
void		ft_putendlc_fd(char *color, char *s, int fd);
void		print_status(int id, t_data *data, char *act, char *col);

void		ft_exit(t_data **data);
uint64_t	get_time(void);
int			f_usleep(uint64_t time);

#endif
