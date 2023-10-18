/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:11:44 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/18 22:32:01 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo		*ph;
	size_t		die;

	ph = (t_philo *)philo;
	die = 0;
	pthread_mutex_lock(&ph->data->mut_start);
	pthread_mutex_unlock(&ph->data->mut_start);
	while (die == 0)
	{
		pthread_mutex_lock(&ph->data->mut_write);
		die = ph->is_die;
		pthread_mutex_unlock(&ph->data->mut_write);

		p_eat(ph, &ph->data->forks[ph->id], &ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		print_status(ph->id, ph->data, THINK, RESET_);
	}
	return ((void *)0);
}

void	set_all_philos_as_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		set_died_philo(&data->philos[i]);
		i++;
	}
}

static int	all_philos_eats_many_times(t_philo *p, uint64_t n, uint64_t eats)
{
	uint64_t	count;
	uint16_t	meals;
	uint64_t			i;

	count = 0;
	meals = 0;
	i = 0;
	while (i < n)
	{
		meals = get_num_of_meals(&p[i]);
		// pthread_mutex_lock(&p[i].data->mut_write);
		// ft_putstrc_fd(GREEN_, ">>>>> philo [", 1);
		// ft_putstrc_fd(GREEN_, ft_itoa(p[i].id), 1);
		// ft_putstrc_fd(GREEN_, "] times eaten: ", 1);
		// ft_putstrc_fd(GREEN_, ft_itoa(meals), 1);
		// ft_putstrc_fd(GREEN_, ", counted: ", 1);
		// ft_putstrc_fd(GREEN_, ft_itoa(count), 1);
		// ft_putstrc_fd(GREEN_, " many times to eat: ", 1);
		// ft_putendlc_fd(GREEN_, ft_itoa(eats), 1);
		// pthread_mutex_unlock(&p[i].data->mut_write);
		if (meals >= eats)
		{
			
			count++;
		}
		else
			return (0);
		i++;
	}
	i = 0;
	//count++;
	if (count == n)
	{
		//set_all_philos_as_died(p[i].data);
		// pthread_mutex_lock(&p[i].data->mut_write);
		// ft_putstrc_fd(GREEN_, "Times eaten: ", 1);
		// ft_putendlc_fd(GREEN_, ft_itoa(count), 1);
		// pthread_mutex_unlock(&p[i].data->mut_write);
		
		return (1);
	}
	return (0);
}

void	*exit_checker(void *data)
{
	t_data		*d;
	int			i;
	size_t		end;
	uint64_t	curr_time;
	uint64_t	start_eat;

	d = (t_data *)data;
	i = 0;
	end = 0;
	//pthread_mutex_unlock(&d->mut_start);
	//d->start_time = get_time();
	
	while (end == 0)
	{
		i = 0;
		while (i < d->num_philos)
		{
			if (d->many_times_to_eat != 0 && all_philos_eats_many_times(d->philos, (uint64_t)d->num_philos, d->many_times_to_eat) == 1)
			{
				print_die(d->philos[i].id, d, DIE, RED_);
				end = 1;
				//finish_routine(d, &end, i);
				print_status(d->philos[i].id, d, " All philos eats many times", GREEN_);
				break ;
			}
			pthread_mutex_lock(d->philos[i].mut);
			start_eat = d->philos[i].start_eating;// - d->start_time;
			pthread_mutex_unlock(d->philos[i].mut);
			curr_time = get_time();// - d->start_time;



			
			//  pthread_mutex_lock(&d->mut_write);
			// // ft_putstrc_fd(RED_, "philo id > ", 1);
			// ft_putstrc_fd(RED_, ft_itoa(d->philos[i].id), 1);
			// ft_putstrc_fd(RED_, " ", 1);
			// // ft_putstrc_fd(RED_, "start eating: ", 1);
			// // ft_putendlc_fd(RED_, ft_itoa(start_eat), 1);
			// // ft_putstrc_fd(RED_, "curr time: ", 1);
			// // ft_putendlc_fd(RED_, ft_itoa(curr_time), 1);
			// // ft_putstrc_fd(RED_, ">>>>> time from last eat: ", 1);
			// ft_putendlc_fd(RED_, ft_itoa(curr_time - start_eat), 1);
			// pthread_mutex_unlock(&d->mut_write);



			
			if (curr_time - start_eat > d->t_to_die) //(curr_time) > (start_eat + d->t_to_die))
			{
				print_status(d->philos[i].id, d, "died for many time for last eat", RED_);
				end = 1;
				//finish_routine(d, &end, i);
				break ;
			}
			i++;
		}
		if (end == 1)
		{
			// pthread_mutex_lock(&d->mut_write);
			// d->end_routine = end;
			// pthread_mutex_unlock(&d->mut_write);
			// set_all_philos_as_died(d);
			//print_die(d->philos[i].id, d, DIE, RED_);
			finish_routine(d, &end, d->philos[i].id);
			break ;
		}
	}
	//print_die(d->philos[i].id, d, DIE, RED_);
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
	if (data->num_philos <= 1)
		ft_exit(&data);
	if (init_philos(data) != 0)
		ft_exit(&data);
	else
	{
		pthread_mutex_init(&data->mut_write, NULL);
		pthread_mutex_init(&data->mut, NULL);
		pthread_mutex_init(&data->mut_start, NULL);
		pthread_mutex_lock(&data->mut_start);
		// data->start_time = get_time();
		// pthread_create(&data->controller, NULL, exit_checker, (void *)data);
		while (i < data->num_philos)
		{
			pthread_create(data->philos[i].tid, NULL, work_philo, &data->philos[i]);
			i++;
		}
		data->start_time = get_time();
		//ft_putstrc_fd(GREEN_, "start time: ", 1);
		//ft_putendlc_fd(GREEN_, ft_itoa(data->start_time), 1);
		pthread_create(&data->controller, NULL, exit_checker, (void *)data);
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
