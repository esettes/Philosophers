/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/14 00:53:56 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->start_time = get_time();
	//pthread_mutex_lock(&block);
	//d->aux_var = aux++;

	// all actions while cheching if time > t_to_die
	
	
	// or while forks cant be taken, decrease t_to_die
	// t_to_die is reset if philo start eating(?) --> yes
	if (pthread_mutex_lock(&ph->data->forks[ph->id]) == 0
		&& pthread_mutex_lock(&ph->data->forks[(ph->id + 1)
		% ph->data->num_philos]) == 0)
	{
		ph->start_eating = get_time();
		f_usleep(ph->t_to_eat);
		ph->times_eaten++;
		pthread_mutex_unlock(&ph->data->forks[ph->id]);
		pthread_mutex_unlock(&ph->data->forks[(ph->id + 1)
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
}

int	init_data(t_data **data, int n_philos, useconds_t t_to_sleep, useconds_t t_to_eat,
		useconds_t t_to_die, useconds_t many_times_to_eat)
{
	(*data) = malloc(sizeof(t_data));
	if (!*data)
	{
		ft_putendlc_fd(RED_, "Data allocation error", 1);
		return (EXIT_FAILURE);
	}
	(*data)->num_philos = n_philos;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->num_philos);
	//data->philo = NULL;
	if (!(*data)->forks)
	{
		ft_putendlc_fd(RED_, "Forks allocation error", 1);
		return (EXIT_FAILURE);
	}
	(*data)->t_to_die = t_to_die;
	(*data)->t_to_eat = t_to_eat;
	(*data)->t_to_sleep = t_to_sleep;
	(*data)->many_times_to_eat = many_times_to_eat;
	return (EXIT_SUCCESS);
}

int	init_philos(t_data **data)
{
	int	i;

	i = (*data)->num_philos;
	(*data)->philos = malloc(sizeof(t_philo) * i);
	if (!(*data)->philos)
	{
		ft_putendlc_fd(RED_, "Philosophers allocation error", 1);
		return (EXIT_FAILURE);
	}
	while (i >= 0)
	{
		printf("i = %d\n", i);
		(*data)->philos[i].id = i + 1;
		(*data)->philos[i].data = *data;
		(*data)->philos[i].mut = malloc(sizeof(pthread_mutex_t));
		(*data)->philos[i].times_eaten = 0;
		(*data)->philos[i].t_to_die = (*data)->t_to_die;
		(*data)->philos[i].t_to_eat = (*data)->t_to_eat;
		(*data)->philos[i].t_to_sleep = (*data)->t_to_sleep;
		(*data)->philos[i].many_times_to_eat = (*data)->many_times_to_eat;
		(*data)->philos[i].start_eating = 0;
		(*data)->philos[i].start_sleeping = 0;
		(*data)->philos[i].start_thinking = 0;
		(*data)->philos[i].start_time = 0;
		(*data)->philos[i].tid = malloc(sizeof(pthread_t));
		if (!(*data)->philos[i].tid)
		{
			ft_putendlc_fd(RED_, "Thread allocation error", 1);
			return (EXIT_FAILURE);
		}
		i--;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	pthread_t	tid1;
	pthread_t	tid2;
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
	ft_putendlc_fd(RED_, "Hey", 1);
	pthread_mutex_init(data->forks, NULL);
	
	
	
	for (int i = 0; i < 100 ; i++)
		pthread_create(&data->philos[i].tid, NULL, work_philo, (void *)data);

	
	for (int i = 0; i < 100 ; i++)
		pthread_join(data->philos[i].tid, NULL);
	
	pthread_mutex_destroy(data->forks);
	ft_putendlc_fd(RED_, "Finish program", 1);
	for (int i = 0; i < 100 ; i++)
		free(data->philos[i].tid);
	// for (int i = 0; i < 100 ; i++)
	// 	free(data->forks[i]);
	free(data->philos);
	free(data->forks);
	free(data);
}
