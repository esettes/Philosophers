/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/08/31 20:53:02 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int aux = 1;

void	*work_philo(void *data)
{
	t_data	*d;

	d = (t_data *)data;
	printf("aux: %d\n", aux++);
}

void	init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->philo = NULL;
	data->t_to_die = 0;
	data->t_to_eat = 0;
	data->t_to_sleep = 0;
	data->many_times_to_eat = 0;
}

int	main(int argc, char *argv[])
{
	pthread_t	thread;
	t_data		*data;

	init_data(data);
	for (int i = 0; i < 100; i++)
		pthread_create(&thread, NULL, work_philo, (void *)data);
	pthread_exit(NULL);
	free(data);
}
