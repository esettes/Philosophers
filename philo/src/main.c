/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/14 23:29:47 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*work_philo(void *data)
// {
// 	t_data	*d;

// 	d = (t_data *)data;
	
// 	if (pthread_mutex_lock(d->forks[d->philos->id]) == 0
// 		&& pthread_mutex_lock(d->forks[(d->philos->id + 1)
// 		% d->num_philos]) == 0)
// 	{
// 		ph->start_eating = get_time();
// 		f_usleep(ph->t_to_eat);
// 		ph->times_eaten++;
// 		pthread_mutex_unlock(&ph->data->forks[ph->id]);
// 		pthread_mutex_unlock(&ph->data->forks[(ph->id + 1)
// 		% ph->data->num_philos]);
// 	}
// 	// else
// 	// {

// 	// }

// 	print_status(ph);
// 	ph->start_sleeping = get_time();
// 	f_usleep(ph->t_to_sleep);
// 	print_status(ph);
// 	if (ph->t_to_sleep > ph->t_to_die)
// 	{
// 		// philo dies
// 	}
// 	ph->start_thinking = get_time();
// 	print_status(ph);
	
// 	// if (ph->many_times_to_eat == ph->times_eaten)
// 	// {
// 	// 	// philo die
// 	// }
// 	return ((void *)0);
// }

void	*work_philo(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	
	if (pthread_mutex_lock(ph->data->forks[ph->id]) == 0
		&& pthread_mutex_lock(ph->data->forks[(ph->id + 1)
		% ph->data->num_philos]) == 0)
	{
		ph->start_eating = get_time();
		f_usleep(ph->t_to_eat);
		ph->times_eaten++;
		pthread_mutex_unlock(ph->data->forks[ph->id]);
		pthread_mutex_unlock(ph->data->forks[(ph->id + 1)
			% ph->data->num_philos]);
	}
	// else
	// {

	// }

	print_status(ph);
	ph->start_sleeping = get_time();
	f_usleep(ph->t_to_sleep);
	print_status(ph);
	if (ph->t_to_sleep > ph->t_to_die)
	{
		// philo dies
	}
	ph->start_thinking = get_time();
	print_status(ph);
	
	// if (ph->many_times_to_eat == ph->times_eaten)
	// {
	// 	// philo die
	// }
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	if (argc <= 1 && argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [num_of_philosophers] [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
		exit(EXIT_FAILURE);
	}





	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		exit(EXIT_FAILURE);




	if (init_philos(&data) != 0)
		exit(EXIT_FAILURE);

	data->start_time = get_time();


	pthread_mutex_init(data->forks, NULL);
	pthread_mutex_init(data->mut, NULL);






	for (int i = 0; i <= data->num_philos ; i++)
		pthread_create(data->philos[i]->tid, NULL, work_philo, (void *)data->philos[i]);

	for (int i = 0; i <= data->num_philos ; i++)
		pthread_join(data->philos[i]->tid, NULL);



	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(data->mut);
	ft_putendlc_fd(YELLOW_, "Finish program", 1);
	for (int i = 0; i <= data->num_philos ; i++)
	{
		if (data->philos[i]->tid)
			free(data->philos[i]->tid);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->mut)
		free(data->mut);
	free(data);
}
