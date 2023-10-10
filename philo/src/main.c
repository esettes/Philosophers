/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/10 21:27:27 by iostancu         ###   ########.fr       */
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
	//pthread_mutex_lock(ph->data->mut_start);
	while (die == 0 && end == 0)
	{
		// set_mutex_val(&ph->data->mut_write, &end, ph->data->end_routine);
		// set_mutex_val(&ph->data->mut_write, &die, ph->is_die);
		pthread_mutex_lock(ph->data->mut_write);
		end = ph->data->end_routine;
		die = ph->is_die;
		pthread_mutex_unlock(ph->data->mut_write);
		if (die == 1 || end == 1)
			break ;
		p_eat(ph);
		
		//p_think(ph);
		print_status(ph->id, ph->data, THINK, RESET_);
	}
	return ((void *)0);
}

static int	all_philos_eats_many_times(pthread_mutex_t *mut, t_philo *p, int n, int start)
{
	u_int64_t	eats;
	u_int64_t	times;
	int			i;

	eats = 0;
	times = 0;
	i = 0;
	while (i < n)
	{
		//if (p[i]->is_die == 0)
		//{
			//set_mutex_val(&mut, &eats, p[start].times_eaten);
			// eats = get_mutex_val(&mut, p[start].times_eaten);
			// times = get_mutex_val(&mut, p[start].data->many_times_to_eat);
			pthread_mutex_lock(mut);
			eats = p[i].times_eaten;
			times = p[i].data->many_times_to_eat;
			pthread_mutex_unlock(mut);
			if (eats >= times)
			{
				pthread_mutex_lock(mut);
				//set_mutex_val(&mut, &p[start].is_die, 1);
				p[i].is_die = 1;
				pthread_mutex_unlock(mut);
			}
			else
				return (0);
		//}
		i++;
	}
	(void)start;
	return (1);
}


void	*exit_checker(void *data)
{
	t_data		*d;
	int			i;
	u_int64_t	curr_time;
	u_int64_t	aux;
	size_t		end;

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
				pthread_mutex_lock(d->mut_write);
				d->end_routine = 1;
				pthread_mutex_unlock(d->mut_write);
				break ;
			}
			if (all_philos_eats_many_times(d->mut_write ,d->philos, d->num_philos,  i) == 1)
			{
				pthread_mutex_lock(d->mut_write);
				d->end_routine = 1;
				pthread_mutex_unlock(d->mut_write);
				print_status(d->philos[i].id, d, " All philos eats many times", GREEN_);
				break ;
			}
			curr_time = get_time() - d->start_time;
			pthread_mutex_lock(d->mut_write);
			aux = d->philos[i].start_eating;
			pthread_mutex_unlock(d->mut_write);
			if ((curr_time) > (aux + d->t_to_die))
			{
				print_status(d->philos[i].id, d, "died for many time for last eat", RED_);
				pthread_mutex_lock(d->mut_write);
				d->end_routine = 1;
				pthread_mutex_unlock(d->mut_write);
				break ;
			}
			i++;
		}
		pthread_mutex_lock(d->mut_write);
		end = d->end_routine;
		pthread_mutex_unlock(d->mut_write);
		if (end == 1)
		{
			// i = 0;
			// while (i < d->num_philos)
			// {
			// 	d->philos[i].is_die = 1;
			// 	i++;
			// }
			print_status(d->philos[i].id, d, " hello", GREEN_);
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
	pthread_mutex_init(data->mut_start, NULL);
	pthread_create(&data->controller, NULL, exit_checker, (void *)data);
	for (int i = 0; i < data->num_philos ; i++)
		pthread_create(data->philos[i].tid, NULL, work_philo, &data->philos[i]);
	//f_usleep(10);
	//pthread_mutex_unlock(data->mut_start);
	while (i < data->num_philos)
	{
		if (data->philos[i].tid)
			pthread_join(*data->philos[i].tid, NULL);
		i++;
	}
	pthread_join(data->controller, NULL);
	i = 0;

	// while (i < data->num_philos)
	// {
	// 	if (data->philos[i].is_die == 0)
	// 		i = 0;
	// 	i ++;
	// }
	i = 0;
	while (i < data->num_philos)
	{
		//if (&data->forks[i])
			pthread_mutex_destroy(&data->forks[i]);
			//free(&data->forks[i]);
			free(data->philos[i].tid);
		i++;
	}
	
	
	//ft_exit(&data);
	pthread_mutex_destroy(data->mut_write);
	pthread_mutex_destroy(data->mut_start);
	//free(data->controller);
	free(data->forks);
	free(data->mut_write);
	free(data->mut_start);
	free(data->philos);
	free (data);
	

	
	//f_usleep(500);
}
