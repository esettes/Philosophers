/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/07 00:16:02 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int aux = 1;

void	*work_philo(void *data)
{
	t_data	*d;

	d = (t_data *)data;
	d->aux_var = aux++;
	ft_putendlc_fd(BLUE_, ft_itoa(d->philo->tid), 1);
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
	if (!data)
	{
		ft_putendlc_fd(RED_, "Malloc error", 1);
		exit(EXIT_FAILURE);
	}
	data->philo = (t_philo *)malloc(sizeof(t_philo) * 2);
	if (!data->philo)
	{
		ft_putendlc_fd(RED_, "Malloc error", 1);
		exit(EXIT_FAILURE);
	}
	data->philo[0].tid = malloc(sizeof(pthread_t));
	data->philo[1].tid = malloc(sizeof(pthread_t));
	if (!data->philo[0].tid || !data->philo[1].tid)
	{
		ft_putendlc_fd(RED_, "Malloc error", 1);
		exit(EXIT_FAILURE);
	}
	

	pthread_create(&tid1, NULL, work_philo, (void *)data);
	pthread_create(&tid2, NULL, work_philo, (void *)data);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	ft_putendlc_fd(RED_, "Finish program", 1);
	free(data->philo[0].tid);
	free(data->philo[1].tid);
	free(data->philo);
	free(data);
}
