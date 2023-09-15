/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/15 21:13:55 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;

	//printf("ph->data->forks[%i]: %p\n", ph->id, ph->data->forks[ph->id]);
	if (pthread_mutex_lock(ph->data->forks[ph->id]) == 0
		&& pthread_mutex_lock(ph->data->forks[(ph->id + 1)
		% ph->data->num_philos]) == 0)
	{
		ph->fork_time = get_time();
		print_status(ph, ph->fork_time, "has taken a fork", BLUE_);
		ph->start_eating = get_time();
		f_usleep(ph->t_to_eat);
		print_status(ph, ph->start_eating, "is eating", VIOLET_);
		ph->eat = 1;
		ph->times_eaten++;
		pthread_mutex_unlock(ph->data->forks[ph->id]);
		pthread_mutex_unlock(ph->data->forks[(ph->id + 1)
			% ph->data->num_philos]);
		print_status(ph, ph->start_eating, "has leaving forks", VIOLET_);
	}
	// else
	// {

	// }
	if (ph->times_eaten >= ph->many_times_to_eat)
	{
		print_status(ph, get_time(), "die", RED_);
	}
//	if (ph->sleep == 0)
	{
		ph->start_sleeping = get_time();
		f_usleep(ph->t_to_sleep);
		ph->sleep = 1;
//	}
	
	print_status(ph, ph->start_sleeping, "is sleeping", CYAN_);
	if (ph->t_to_sleep < ph->t_to_die)
	{
		print_status(ph, get_time(), "die", RED_);
	}
	ph->start_thinking = get_time();
	print_status(ph, ph->start_thinking, "is thinking", RESET_);
	
	// if (ph->many_times_to_eat == ph->times_eaten)
	// {
	// 	// philo die
	// }
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	u_int64_t	t;
	int	i;

	i = 0;
	if (argc <= 1 && argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [num_of_philosophers] [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
		exit(EXIT_FAILURE);
	}

	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		exit(EXIT_FAILURE);


	if (init_philos(data) != 0)
		exit(EXIT_FAILURE);
	
	t = get_time();
	data->epoch_time = get_time();
	data->start_time = 0;

	while (i <= data->num_philos)
	{
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->mut_write, NULL);



	for (int i = 0; i < data->num_philos ; i++)
		pthread_create(data->philos[i]->tid, NULL, work_philo, (void *)data->philos[i]);

	for (int i = 0; i < data->num_philos ; i++)
		pthread_join(*data->philos[i]->tid, NULL);

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->mut_write);
	ft_putendlc_fd(YELLOW_, "Finish program", 1);
	i = 0;
	while (data->philos[i]->tid)
	{
		free(data->philos[i]->tid);
		i++;
	}
	i = 0;
	while (data->philos[i])
	{
		free(data->philos[i]);
		i++;
	}
	if (data->philos)
		free(data->philos);
	i = 0;
	while (data->forks)
	{
		free(data->forks[i]);
		i++;
	}
	if (data->forks)
		free (data->forks);
	if (data->mut_write)
		free(data->mut_write);
	free(data);
}
