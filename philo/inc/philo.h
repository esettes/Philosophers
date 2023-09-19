/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:45:28 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/19 20:59:34 by iostancu         ###   ########.fr       */
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
 * eat --> sleep --> think 
 * think --> eat --> sleep
 */
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		*tid;
	int				id;
	pthread_mutex_t	mut_write;
	u_int64_t		fork_time;
	u_int64_t		start_eating;
	u_int64_t		finish_eat;
	u_int64_t		start_thinking;
	u_int64_t		start_sleeping;
	u_int64_t		t_to_die;
	u_int64_t		t_to_eat;
	u_int64_t		t_to_sleep;
	u_int64_t		die_time;
	size_t			eat;
	size_t			sleep;
	size_t			think;
	size_t			many_times_to_eat;
	size_t			times_eaten;
}				t_philo;

typedef struct s_data
{
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*mut_write;
	int				num_philos;
	uint64_t		start_time;
	uint64_t		epoch_time;
	u_int64_t		t_to_die;
	u_int64_t		t_to_eat;
	u_int64_t		t_to_sleep;
	u_int64_t		many_times_to_eat;
}				t_data;

void		ft_putendlc_fd(char *color, char *s, int fd);
void		ft_putstrc_fd(char *color, char *s, int fd);
void		ft_putcolor_fd(char *color, int fd);
void		ft_resetcolor_fd(int fd);
void		ft_putendl_fd(char *s, int fd);

char		*ft_itoa(u_int64_t n);
u_int64_t	ft_atoi(const char *str);

u_int64_t	get_time(void);
u_int64_t	get_time_in_ms(u_int64_t start_time);
int			f_usleep(u_int64_t time);
//void		print_status(t_philo *philo);
void		print_status(t_philo *p, u_int64_t t, char *act, char *col);


int			init_data(t_data **data, int n_philos, u_int64_t t_to_sleep, u_int64_t t_to_eat,
						u_int64_t t_to_die, int many_times_to_eat);
int			init_philos(t_data *data);
void		*ft_exit(t_data *data);

#endif
