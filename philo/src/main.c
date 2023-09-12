/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/12 23:15:35 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int aux = 1;
pthread_mutex_t	block;

void	*work_philo(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->start_time = get_time();
	//pthread_mutex_lock(&block);
	//d->aux_var = aux++;

	// all actions while cheching if time > t_to_die
	
	
	

	// or while forks cant be taken, decrease t_to_die
	// t_to_die is reset if philo start eating(?)
	if (pthread_mutex_lock(ph->data->forks[ph->id]) == 0
		&& pthread_mutex_lock(ph->data->forks[(ph->id + 1)
		% ph->data->num_philos]) == 0)
	{
		// start eating
		//take forks

		// unlock
	}
	// start sleeping

	// start thinking
	
	ft_putendlc_fd(BLUE_, ft_itoa(ph->tid), 1);
	ft_putendl_fd("aux: ", 1);
	ft_putendl_fd(ft_itoa(d->aux_var), 1);
	pthread_mutex_unlock(&block);
}

void	init_data(t_data **data, useconds_t t_to_sleep, useconds_t t_to_eat,
		useconds_t t_to_die, useconds_t many_times_to_eat)
{
	*data = (t_data *)malloc(sizeof(t_data *));
	//data->philo = NULL;
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
		data->philos[data->num_philos].data = &data;
	}
}

int	main(int argc, char *argv[])
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_data		*data;

	init_data(&data, argv[2], argv[3], argv[4], argv[5]);
	
	init_philos(data);
	
	pthread_mutex_init(data->forks, NULL);
	
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
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
		{
			ft_putendlc_fd(RED_, "Fork allocation error", 1);
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < 100 ; i++)
		pthread_create(&data->philos[i].tid, NULL, work_philo, (void *)data);

	
	for (int i = 0; i < 100 ; i++)
		pthread_join(data->philos[i].tid, NULL);
	
	pthread_mutex_destroy(data->forks);
	ft_putendlc_fd(RED_, "Finish program", 1);
	for (int i = 0; i < 100 ; i++)
		free(data->philos[i].tid);
	free(data->philos);
	free(data);
}
