/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:06:57 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/20 23:06:34 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data **data, int n_philos, u_int64_t t_to_sleep, u_int64_t t_to_eat,
		u_int64_t t_to_die, int many_times_to_eat)
{
	int	i;

	i = 0;
	(*data) = malloc(sizeof(t_data));
	if (!*data)
	{
		ft_putendlc_fd(RED_, "Data allocation error", 1);
		return (EXIT_FAILURE);
	}
	(*data)->num_philos = n_philos;
	(*data)->forks = malloc(sizeof(pthread_mutex_t *) * ((*data)->num_philos + 1));
	(*data)->mut_write = malloc(sizeof(pthread_mutex_t) * (*data)->num_philos);
	//data->philo = NULL;
	
	if (!(*data)->forks)
	{
		ft_putendlc_fd(RED_, "Data mutexes allocation error", 1);
		return (EXIT_FAILURE);
	}
	(*data)->forks[(*data)->num_philos] = NULL;
	while (i <= (*data)->num_philos)
	{
		(*data)->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!(*data)->forks[i])
		{
			ft_putendlc_fd(RED_, "Data forks allocation error", 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	(*data)->t_to_die = t_to_die;
	(*data)->t_to_eat = t_to_eat;
	(*data)->t_to_sleep = t_to_sleep;
	(*data)->many_times_to_eat = many_times_to_eat;
	return (EXIT_SUCCESS);
}

static int	set_philo(t_philo **philo, int id, t_data **data)
{
	// philo->id = id;
	// philo->times_eaten = 0;
	// philo->t_to_die = 0;
	// philo->t_to_eat = 0;
	// philo->t_to_sleep = 0;
	// philo->many_times_to_eat = 0;
	// philo->start_eating = 0;
	// philo->start_sleeping = 0;
	// philo->start_thinking = 0;
	// philo->start_time = 0;
	// philo->tid = malloc(sizeof(pthread_t));
	(*philo)->id = id;
	(*philo)->data = *data;
	(*philo)->times_eaten = 0;
	(*philo)->t_to_die = (*data)->t_to_die;
	(*philo)->t_to_eat = (*data)->t_to_eat;
	(*philo)->t_to_sleep = (*data)->t_to_sleep;
	(*philo)->many_times_to_eat = (*data)->many_times_to_eat;
	(*philo)->start_eating = 0;
	(*philo)->start_sleeping = 0;
	(*philo)->eat = 0;
	(*philo)->sleep = 0;
	(*philo)->think = 0;
	(*philo)->is_die = 0;
	(*philo)->l_fork = 0;
	(*philo)->r_fork = 0;
	(*philo)->finish_eat = 0;
	pthread_mutex_init(&(*philo)->mut_eat, NULL);
	(*philo)->tid = malloc(sizeof(pthread_t));
	if (!(*philo)->tid)
	{
		ft_putendlc_fd(RED_, "Thread allocation error", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_philos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * (data->num_philos + 1));
	
	data->philos[data->num_philos] = NULL;
	while (i <= data->num_philos)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		i++;
	}
	if (!data->philos)
	{
		ft_putendlc_fd(RED_, "Philosophers allocation error", 1);
		return (EXIT_FAILURE);
	}
	i = data->num_philos - 1;
	while (i >= 0)
	{
		
		if (set_philo(&data->philos[i], i, &data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i--;
	}
	return (EXIT_SUCCESS);
}
