/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:11:44 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/13 00:48:22 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo		*ph;
	size_t		end;
	size_t		die;

	ph = (t_philo *)philo;
	end = 0;
	die = 0;
	pthread_mutex_lock(&ph->data->mut_start);
	pthread_mutex_unlock(&ph->data->mut_start);
	while (die == 0)
	{
		p_
		print_status(ph->id, ph->data, THINK, RESET_);
	}
	return ((void *)0);
}

void	*exit_checker(void *data)
{
	t_data	*d;
	int		i;
	int		eats;

	d = (t_data *)data;
	i = 0;
	eats = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_lock(&d->mut_write);
		ft_putendlc_fd(BLUE_, "Hiii", 1);
		pthread_mutex_unlock(&d->mut_write);
		i++;
	}
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 0;
	if (argc <= 1 || argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [num_of_philosophers] [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
	}
	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		 ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		ft_exit(&data);
	if (init_philos(data) != 0)
		ft_exit(&data);
	else
	{
		init_forks(data, &data->forks);
		pthread_mutex_init(&data->mut_write, NULL);
		pthread_mutex_init(&data->mut_start, NULL);
		pthread_mutex_lock(&data->mut_start);
		data->start_time = get_time();
		pthread_create(&data->controller, NULL, exit_checker, (void *)data);
		while (i < data->num_philos)
		{
			pthread_create(data->philos[i].tid, NULL, work_philo, &data->philos[i]);
			i++;
		}
		pthread_mutex_unlock(&data->mut_start);
		i = 0;
		while (i < data->num_philos)
		{
			pthread_join(*data->philos[i].tid, NULL);
			i++;
		}
		pthread_join(data->controller, NULL);

		pthread_mutex_destroy(&data->mut_write);
		pthread_mutex_destroy(&data->mut_start);
		ft_exit(&data);
	}
}
