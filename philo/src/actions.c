/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/20 20:05:44 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_sleep(t_philo *ph)
{
	if (ph->sleep == 0 && ph->eat == 1 && ph->think == 0)
	{
		ph->start_sleeping = get_time();
		f_usleep(ph->t_to_sleep);
		print_status(ph, ph->start_sleeping, "is sleeping", CYAN_);
		ph->sleep = 1;
	}
}

void	p_eat(t_philo *ph)
{
	
}
