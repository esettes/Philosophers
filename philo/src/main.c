/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/21 18:13:01 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*log_checker(void *philo)
{
	t_philo		*ph;
	u_int64_t	curr_time;
	u_int64_t	aux;

	ph = (t_philo *)philo;
	f_usleep(20);
	
	while (ph->is_die == 0)
	{
		
		// if (ph->r_fork == 1)
		// 	print_status(ph, "has taken a fork", YELLOW_);
		// if (ph->l_fork == 1)
		// 	print_status(ph, "has taken a fork", YELLOW_);
		if (ph->is_die == 1)
			break ;
		// if (ph->eat == 1)
		// 	print_status(ph, "is eating", VIOLET_);
		// if (ph->sleep == 1)
		// 	print_status(ph, "is sleeping", CYAN_);
		
		if (ph->t_to_die < ph->t_to_eat)
		{
			print_status(ph, "died eating > dying", RED_);
			pthread_mutex_unlock(ph->data->forks[ph->id]);
			pthread_mutex_unlock(ph->data->forks[(ph->id + 1)
				% ph->data->num_philos]);
			ph->is_die = 1;
			break ;
		}
		if (ph->times_eaten >= ph->many_times_to_eat)
		{
			//print_status(ph, "died for eat many times", RED_);
			ph->is_die = 1;
			break ;
		}
		
		pthread_mutex_lock(ph->mut_eat);
		curr_time = get_time();
		curr_time -= ph->data->start_time;
		aux = ph->start_eating;
		pthread_mutex_unlock(ph->mut_eat);
		if ((curr_time) > (aux + ph->t_to_die))
		{
			
			pthread_mutex_lock(ph->data->mut_write);
			ft_putstrc_fd(GREEN_, ft_itoa(aux + ph->t_to_die), 1);
			ft_putendlc_fd(GREEN_, "ms to die", 1);
			ft_putstrc_fd(GREEN_, ft_itoa(curr_time), 1);
			ft_putendlc_fd(GREEN_, "ms current time", 1);
			pthread_mutex_unlock(ph->data->mut_write);
			
			//print_status(ph, "died for many time for last eat", RED_);
			ph->is_die = 1;
			break ;
		}
		
	}
	print_status(ph, "died", RED_);
	//ph->is_die = 1;
	ft_exit(ph->data);
	return ((void *)0);
}

void	*work_philo(void *philo)
{
	t_philo		*ph;
	u_int64_t	curr_time;

	ph = (t_philo *)philo;

	pthread_create(&ph->log, NULL, log_checker, (void *)ph);
	while (ph->is_die == 0)
	{
		p_eat(ph);
		if (ph->is_die == 1)
			return (ft_exit(ph->data));
		p_sleep(ph);
	}
	return ((void *)0);
}

void	*exit_checker(void *data)
{
	t_data	*d;
	int		i;

	d = (t_data *)data;
	while (1)
	{
		i = 0;
		while (i < d->num_philos)
		{
			if (d->philos[i]->is_die == 1)
			{
				ft_exit(d);
			}
			i++;
		}
	}
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	int	i;

	i = 0;
	if (argc <= 1 || argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [num_of_philosophers] [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
		exit(EXIT_SUCCESS);
	}

	if (init_data(&data, (u_int64_t)ft_atoi(argv[1]),  (u_int64_t)ft_atoi(argv[2]),  (u_int64_t)ft_atoi(argv[3]),
		 (u_int64_t)ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		ft_exit(data);


	if (init_philos(data) != 0)
		ft_exit(data);

	data->start_time = get_time();
	ft_putstrc_fd(YELLOW_, ft_itoa(data->start_time), 1);
	ft_putendlc_fd(YELLOW_, "ms start_time -------------------", 1);
	while (i <= data->num_philos)
	{
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	
	pthread_mutex_init(data->mut_write, NULL);



	for (int i = 0; i < data->num_philos ; i++)
		pthread_create(data->philos[i]->tid, NULL, work_philo, (void *)data->philos[i]);

	//pthread_create(&data->exit_, NULL, exit_checker, (void *)data);

	ft_exit(data);
}
