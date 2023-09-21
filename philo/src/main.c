/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/21 21:41:50 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo		*ph;
	u_int64_t	curr_time;

	ph = (t_philo *)philo;

	while (ph->is_die == 0)
	{
		p_eat(ph);
		// if (ph->is_die == 1)
		// 	return (ft_exit(ph->data));
		p_sleep(ph);
	}
	return ((void *)0);
}

void	*exit_checker(void *data)
{
	t_data		*d;
	int			i;
	u_int64_t	curr_time;
	u_int64_t	aux;

	
	d = (t_data *)data;
	//ft_putendlc_fd(BLUE_, "o oo o o oooooo o o oo O O O OO O O", 1);
	f_usleep(20);
	while (1)
	{
		i = 0;
		
		while (i < d->num_philos)
		{
			// pthread_mutex_lock(d->mut_write);
			// ft_putstrc_fd(GREEN_, ft_itoa(d->philos[i]->id), 1);
			// ft_putendlc_fd(GREEN_, ". philo", 1);
			// ft_putstrc_fd(GREEN_, ft_itoa(d->philos[i]->times_eaten), 1);
			// ft_putendlc_fd(GREEN_, " times eaten", 1);
			// pthread_mutex_unlock(d->mut_write);
			if (d->t_to_die < d->t_to_eat)
			{
				pthread_mutex_unlock(d->forks[d->philos[i]->id]);
				pthread_mutex_unlock(d->forks[(d->philos[i]->id + 1)
					% d->num_philos]);
				print_status(d->philos[i], "time to die > time to eat", RED_);
				d->philos[i]->is_die = 1;
				print_status(d->philos[i], DIE, RED_);
				ft_exit(d);
				//break ;
			}
			if (d->philos[i]->times_eaten >= d->many_times_to_eat)
			{
				print_status(d->philos[i], "died for eat many times", RED_);
				d->philos[i]->is_die = 1;
				//break ;
				print_status(d->philos[i], DIE, RED_);
				ft_exit(d);
			}
			pthread_mutex_lock(d->philos[i]->mut_eat);
			curr_time = get_time();
			curr_time -= d->start_time;
			aux = d->philos[i]->start_eating;
			pthread_mutex_unlock(d->philos[i]->mut_eat);
			if ((curr_time) > (aux + d->t_to_die))
			{
				print_status(d->philos[i], "died for many time for last eat", RED_);
				d->philos[i]->is_die = 1;
				//break ;
				print_status(d->philos[i], DIE, RED_);
				ft_exit(d);
			}
			i++;
		}
		if (d->philos[i]->is_die == 1)
			break ;
	}
	print_status(d->philos[i], DIE, RED_);
	ft_exit(d);
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
		exit(EXIT_SUCCESS);
	}
	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		 ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		ft_exit(data);
	if (init_philos(data) != 0)
		ft_exit(data);
	data->start_time = get_time();
	while (i <= data->num_philos)
	{
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	
	pthread_mutex_init(data->mut_write, NULL);


	pthread_create(&data->controller, NULL, exit_checker, (void *)data);

	for (int i = 0; i < data->num_philos ; i++)
		pthread_create(data->philos[i]->tid, NULL, work_philo, (void *)data->philos[i]);

	

	ft_exit(data);
}
