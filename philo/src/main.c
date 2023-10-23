/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:11:44 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/23 22:46:18 by iostancu         ###   ########.fr       */
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
		p_eat(ph, &ph->data->forks[ph->id], &ph->data->forks[(ph->id + 1)
			% ph->data->num_philos]);
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
	uint64_t	i;

	count = 0;
	meals = 0;
	i = 0;
	while (i < n)
	{
		meals = get_num_of_meals(&p[i]);
		if (meals >= eats)
			count++;
		else
			return (0);
		i++;
	}
	i = 0;
	if (count == n)
		return (1);
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
	while (end == 0)
	{
		i = -1;
		while (++i < d->num_philos)
		{
			if (d->times_to_eat != 0 && all_philos_eats_many_times
				(d->philos, (uint64_t)d->num_philos, d->times_to_eat) == 1)
			{
				end = 1;
				break ;
			}
			pthread_mutex_lock(d->philos[i].mut);
			start_eat = d->philos[i].start_eating;
			pthread_mutex_unlock(d->philos[i].mut);
			curr_time = get_time();
			if ((curr_time - start_eat) > d->t_to_die)
			{
				end = 1;
				break ;
			}
		}
		if (end == 1)
		{
			finish_routine(d, &end, d->philos[i].id);
			break ;
		}
	}
	return ((void *)0);
}

int is_correct_input(char *argv[])
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_arg(argv[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = -1;
	if (argc <= 1 || argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [n_philos] [die_time] [eat_time] ", 1);
		ft_putendlc_fd(YELLOW_, "[sleep_time] opc[times_to_eat]", 1);
	}
	/** look if is correct input */
	if (is_correct_input(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
			ft_atoi(argv[4]), ft_atoi(argv[5])) == EXIT_FAILURE)
		ft_exit(&data, 0);
	if (init_philos(data) == EXIT_FAILURE)
		ft_exit(&data, 0);
	else
	{
		pthread_mutex_init(&data->mut_write, NULL);
		pthread_mutex_init(&data->mut, NULL);
		pthread_mutex_init(&data->mut_start, NULL);
		pthread_mutex_lock(&data->mut_start);
		
		while (++i < data->num_philos)
			pthread_create(data->philos[i].tid, NULL, work_philo,
				&data->philos[i]);
		data->start_time = get_time();
		pthread_create(&data->controller, NULL, exit_checker, (void *)data);
		pthread_mutex_unlock(&data->mut_start);
		i = -1;
		while (++i < data->num_philos)
			pthread_join(*data->philos[i].tid, NULL);
		pthread_join(data->controller, NULL);
		pthread_mutex_destroy(&data->mut_write);
		pthread_mutex_destroy(&data->mut_start);
		pthread_mutex_destroy(&data->mut);
		ft_exit(&data, 1);
	}
}
