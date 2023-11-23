/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:13:09 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/20 21:40:02 by iostancu         ###   ########.fr       */
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
# include <limits.h>

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
	unsigned long int	times_eaten;
	size_t				is_die;
	unsigned long int	start_eating;
	size_t				r_fork;
	size_t				l_fork;
	pthread_mutex_t		*mut;
}				t_philo;

typedef struct s_data
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	size_t				*eat_forks;
	pthread_t			controller;
	pthread_mutex_t		mut_write;
	pthread_mutex_t		mut_start;
	pthread_mutex_t		mut;
	size_t				end_routine;
	int					num_philos;
	unsigned long int	start_time;
	unsigned long int	t_to_die;
	unsigned long int	t_to_eat;
	unsigned long int	t_to_sleep;
	unsigned long int	times_to_eat;
}				t_data;

int					init_program(t_data **data, int argc, char *argv[]);
void				init_mutexes(t_data *data);

void				p_eat(t_philo *ph, pthread_mutex_t *fork1,
						pthread_mutex_t *fork2);

unsigned long int	ft_atoi(const char *str);
char				*ft_itoa(unsigned long int n);

void				ft_putstrc_fd(char *color, char *s, int fd);
void				ft_putendlc_fd(char *color, char *s, int fd);
void				print_status(int id, t_data *data, char *act, char *col);
void				print_die(int id, t_data *data, char *act, char *col);

void				ft_exit(t_data **data, int mut);
unsigned long int	get_time(void);
int					f_usleep(t_data *data, unsigned long int time);

void				set_all_philos_as_died(t_data *data);
int					all_philos_eats_many_times(t_philo *p, unsigned long int n,
						unsigned long int eats);
int					is_correct_input(int argc, char *argv[]);

unsigned long int	get_num_of_meals(t_philo *ph);

void				finish_routine(t_data *data, size_t *end, int ph_id);
void				set_all_philos_as_died(t_data *data);

#endif
