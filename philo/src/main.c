/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:11:44 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/17 22:53:07 by iostancu         ###   ########.fr       */
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
	while (1)
	{
		// if (is_philo_die(ph, NULL))
		// 	break ;
		// pthread_mutex_lock(&ph->data->mut);
		// end = ph->data->end_routine;
		// pthread_mutex_unlock(&ph->data->mut);
		//end = get_mutex_val(&ph->data->mut, ph->data->end_routine);
		// if (end == 1)
		// 	break ;
		if (p_eat(ph))
			break ;
		//print_status(ph->id, ph->data, THINK, RESET_);
	}
	return ((void *)0);
}

static int	all_philos_eats_many_times(t_philo *p, int n)
{
	uint64_t	eats;
	
	int			i;

	eats = 0;
	i = 0;
	/**
	 * @brief when all philos are die then routine is end, either routine continues
	 * 
	 */
	while (i < n)
	{
		eats = get_num_of_meals(&p[i]);
		if (eats >= p[i].data->many_times_to_eat)
		{
			is_philo_die(&p[i], (void *)1);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

void	*exit_checker(void *data)
{
	t_data		*d;
	int			i;
	size_t		end;
	uint64_t	curr_time;
	uint64_t	aux;

	d = (t_data *)data;
	i = 0;
	end = 0;
	while (end == 0)
	{
		i = 0;
		while (i < d->num_philos)
		{
			if (all_philos_eats_many_times(d->philos, d->num_philos) == 1)
			{
				end = 1;
				print_status(d->philos[i].id, d, " All philos eats many times", GREEN_);
				break ;
			}
			curr_time = get_time() - d->start_time;
			pthread_mutex_lock(d->philos[i].mut);
			aux = d->philos[i].start_eating;
			pthread_mutex_unlock(d->philos[i].mut);
			//aux = get_mutex_val(d->mut_philo[i], d->philos[i].start_eating);
			if ((curr_time) > (aux + d->t_to_die))
			{
				print_status(d->philos[i].id, d, "died for many time for last eat", RED_);
				end = 1;
				break ;
			}
			i++;
		}
		if (end == 1)
		{
			pthread_mutex_lock(&d->mut);
			d->end_routine = end;
			pthread_mutex_unlock(&d->mut);
			break ;
		}
	}
	print_status(d->philos[i].id, d, DIE, RED_);
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
		pthread_mutex_init(&data->mut_write, NULL);
		pthread_mutex_init(&data->mut, NULL);
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
		pthread_mutex_destroy(&data->mut);
		ft_exit(&data);
	}
}
