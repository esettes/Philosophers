/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/14 00:11:41 by iostancu         ###   ########.fr       */
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
	if (pthread_mutex_lock(ph->data->forks[ph->id]) == 0
		&& pthread_mutex_lock(ph->data->forks[(ph->id + 1)
		% ph->data->num_philos]) == 0)
	{
		ph->start_eating = get_time();
		f_usleep(ph->t_to_eat);
		ph->times_eaten++;
		pthread_mutex_unlock(ph->data->forks[ph->id]);
		pthread_mutex_lock(ph->data->forks[(ph->id + 1)
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

int	init_data(t_data **data, useconds_t t_to_sleep, useconds_t t_to_eat,
		useconds_t t_to_die, useconds_t many_times_to_eat)
{
	*data = (t_data *)malloc(sizeof(t_data *));
	if (!*data)
	{
		ft_putendlc_fd(RED_, "Data allocation error", 1);
		exit(EXIT_FAILURE);
	}
	(*data)->num_philos = 100;
	(*data)->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * (*data)->num_philos);
	//data->philo = NULL;
	if (!(*data)->forks)
	{
		ft_putendlc_fd(RED_, "Forks allocation error", 1);
		exit(EXIT_FAILURE);
	}
	(*data)->t_to_die = t_to_die;
	(*data)->t_to_eat = t_to_eat;
	(*data)->t_to_sleep = t_to_sleep;
	(*data)->many_times_to_eat = many_times_to_eat;
}

void	init_philos(t_data *data)
{
	int	i;

	i = data->num_philos;
	while (i--)
	{
		data->philos[data->num_philos].id = i + 1;
		data->philos[data->num_philos].data = data;
		data->philos[data->num_philos].times_eaten = 0;
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_data		*data;

	if (argc == 1)
	{
		ft_putstrc_fd(YELLOW_, "./philo [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
		exit(EXIT_FAILURE);
	}

	init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
	 ft_atoi(argv[4]));
	
	init_philos(data);
	
	pthread_mutex_init(*data->forks, NULL);
	
	if (!data)
	{
		ft_putendlc_fd(RED_, "Malloc error", 1);
		exit(EXIT_FAILURE);
	}
	data->philos = (t_philo *)malloc(sizeof(t_philo) * 100);
	if (!data->philos)
	{
		ft_putendlc_fd(RED_, "Malloc error", 1);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 100 ; i++)
	{
		data->philos[i].tid = malloc(sizeof(pthread_t));
		if (!data->philos[i].tid)
		{
			ft_putendlc_fd(RED_, "Malloc error", 1);
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < 100 ; i++)
	{
		data->philos[i].id = i + 1;
	}
	
	for (int i = 0; i < 100 ; i++)
		pthread_create(&data->philos[i].tid, NULL, work_philo, (void *)data);

	
	for (int i = 0; i < 100 ; i++)
		pthread_join(data->philos[i].tid, NULL);
	
	pthread_mutex_destroy(*data->forks);
	ft_putendlc_fd(RED_, "Finish program", 1);
	for (int i = 0; i < 100 ; i++)
		free(data->philos[i].tid);
	for (int i = 0; i < 100 ; i++)
		free(data->forks[i]);
	free(data->philos);
	free(data->forks);
	free(data);
}
