/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:01:40 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/02 22:56:26 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_all_philos_as_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->mut_write);
		data->philos[i].is_die = 1;
		pthread_mutex_unlock(&data->mut_write);
		i++;
	}
}

unsigned long	get_num_of_meals(t_philo *ph)
{
	unsigned long int	get;

	pthread_mutex_lock(ph->mut);
	get = ph->times_eaten;
	pthread_mutex_unlock(ph->mut);
	return (get);
}

int	all_philos_eats_many_times(t_philo *p, unsigned long n, unsigned long eats)
{
	unsigned long int	count;
	unsigned long int	meals;
	unsigned long int	i;

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

static int	is_valid_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_correct_input(int argc, char *argv[])
{
	int		i;
	size_t	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (argc < 5 || argc > 6)
		ret = EXIT_FAILURE;
	while (argv[++i] && ret == EXIT_SUCCESS)
	{
		if (is_valid_arg(argv[i]) != 0)
			ret = EXIT_FAILURE;
	}
	if (ret == EXIT_FAILURE)
	{
		ft_putstrc_fd(YELLOW_, "./philo [number_of_philos] [time_to_die] ", 1);
		ft_putstrc_fd(YELLOW_, "[time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_sleep] (opt)[many_times_to_eat]", 1);
		ft_putendlc_fd(YELLOW_, " ", 1);
		ft_putendlc_fd(YELLOW_, "All of inputs must be integers > 0", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
