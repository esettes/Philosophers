/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/07 22:07:24 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int aux = 1;
pthread_mutex_t	block;

void	*work_philo(void *data)
{
	t_data	*d;

	d = (t_data *)data;
	pthread_mutex_lock(&block);
	d->aux_var = aux++;
	
	ft_putendlc_fd(BLUE_, ft_itoa(d->philos->tid), 1);
	ft_putendl_fd("aux: ", 1);
	ft_putendl_fd(ft_itoa(d->aux_var), 1);
	pthread_mutex_unlock(&block);
}

void	init_data(t_data **data)
{
	*data = (t_data *)malloc(sizeof(t_data *));
	//data->philo = NULL;
	(*data)->t_to_die = 0;
	(*data)->t_to_eat = 0;
	(*data)->t_to_sleep = 0;
	(*data)->many_times_to_eat = 0;
}

int	main(int argc, char *argv[])
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_data		*data;

	init_data(&data);
	
	
	pthread_mutex_init(&block, NULL);
	
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
		pthread_create(&data->philos[i].tid, NULL, work_philo, (void *)data);

	
	for (int i = 0; i < 100 ; i++)
		pthread_join(data->philos[i].tid, NULL);
	
	pthread_mutex_destroy(&block);
	ft_putendlc_fd(RED_, "Finish program", 1);
	for (int i = 0; i < 100 ; i++)
		free(data->philos[i].tid);
	free(data->philos);
	free(data);
}
