/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/04 21:23:41 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *)philo;

	while (ph->is_die == 0 && ph->data->end_routine == 0)
	{
		p_eat(ph);
		if (ph->is_die == 1 || ph->data->end_routine == 1)
			break ;
		//p_think(ph);
		print_status(ph->id, ph->data, THINK, RESET_);
	}
	return ((void *)0);
}

static int	all_philos_eats_many_times(t_philo **p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (p[i]->times_eaten >= p[i]->data->many_times_to_eat)
		{
			p[i]->is_die = 1;
			//pthread_detach(*p[i].tid);
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
	u_int64_t	curr_time;
	u_int64_t	aux;

	d = (t_data *)data;
	//f_usleep(10);
	while (1)
	{
		i = 0;
		
		while (i < d->num_philos)
		{
			if (d->t_to_die < d->t_to_eat)
			{
				pthread_mutex_unlock(&d->forks[d->philos[i].id]);
				pthread_mutex_unlock(&d->forks[(d->philos[i].id + 1)
					% d->num_philos]);
				d->end_routine = 1;
				break ;
			}
			if (all_philos_eats_many_times(&d->philos, d->num_philos) == 1)
			{
				d->end_routine = 1;
				break ;
			}
			curr_time = get_time() - d->start_time;
			pthread_mutex_lock(d->mut_eat);
			aux = d->philos[i].start_eating;
			pthread_mutex_unlock(d->mut_eat);
			if ((curr_time) > (aux + d->t_to_die))
			{
				print_status(d->philos[i].id, d, "died for many time for last eat", RED_);
				d->end_routine = 1;
				break ;
			}
			i++;
		}
		if (d->end_routine == 1)
		{
			// i = 0;
			// while (i < d->num_philos)
			// {
			// 	d->philos[i].is_die = 1;
			// 	i++;
			// }
			break ;
		}
	}
	print_status(d->philos[i].id, d, DIE, RED_);
	//ft_exit(&d);
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)malloc(sizeof(t_data));
	if (argc <= 1 || argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [num_of_philosophers] [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
		exit(EXIT_SUCCESS);
	}
	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		 ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		ft_exit(&data);
	if (init_philos(data) != 0)
		ft_exit(&data);
	data->start_time = get_time();
	// while (i < data->num_philos)
	// {
	// 	pthread_mutex_init(&data->forks[i], NULL);
	// 	i++;
	// }



	
	pthread_mutex_init(data->mut_write, NULL);
	pthread_mutex_init(data->mut_eat, NULL);
	pthread_create(&data->controller, NULL, exit_checker, (void *)data);
	for (int i = 0; i < data->num_philos ; i++)
		pthread_create(data->philos[i].tid, NULL, work_philo, &data->philos[i]);
	while (i < data->num_philos)
	{
		if (data->philos[i].tid)
			pthread_detach(*data->philos[i].tid);
		i++;
	}
	pthread_join(data->controller, NULL);
	i = 0;

	while (i < data->num_philos)
	{
		if (data->philos[i].is_die == 0)
			i = 0;
		i ++;
	}
	// i = 0;
	// while (i < data->num_philos)
	// {
	// 	if (&data->forks[i])
	// 		pthread_mutex_destroy(&data->forks[i]);
	// 	i++;
	// }
	
	
	//ft_exit(&data);
	pthread_mutex_destroy(data->mut_write);
	pthread_mutex_destroy(data->mut_eat);
	free(data->forks);
	free(data->mut_write);
	free(data->mut_eat);
	free(data->philos);
	free (data);
	

	
	f_usleep(500);
}
