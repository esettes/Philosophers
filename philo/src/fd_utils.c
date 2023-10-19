/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:20:25 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/19 22:45:12 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstrc_fd(char *color, char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*color)
		write(fd, color++, 1);
	while (*s)
		write (fd, s++, 1);
	color = "\x1b[0m";
}

void	ft_putendlc_fd(char *color, char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*color)
		write(fd, color++, 1);
	while (*s)
		write (fd, s++, 1);
	write (fd, "\n", 1);
	color = "\x1b[0m";
}

void	print_status(int id, t_data *data, char *act, char *col)
{
	char	*time_;
	char	*p_id;
	size_t	end;

	pthread_mutex_lock(&data->mut_write);
	end = data->end_routine;
	if (end == 1)
	{
		pthread_mutex_unlock(&data->mut_write);
		return ;
	}
	p_id = ft_itoa(id);
	pthread_mutex_lock(&data->mut);
	time_ = ft_itoa(get_time() - data->start_time);
	pthread_mutex_unlock(&data->mut);
	ft_putstrc_fd(col, time_, 1);
	free(time_);
	ft_putstrc_fd(col, " ", 1);
	ft_putstrc_fd(col, p_id, 1);
	free(p_id);
	ft_putstrc_fd(col, " ", 1);
	ft_putendlc_fd(col, act, 1);
	pthread_mutex_unlock(&data->mut_write);
}

void	print_die(int id, t_data *data, char *act, char *col)
{
	char	*time_;
	char	*p_id;

	pthread_mutex_lock(&data->mut_write);
	p_id = ft_itoa(id);
	time_ = ft_itoa(get_time() - data->start_time);
	ft_putstrc_fd(col, time_, 1);
	free(time_);
	ft_putstrc_fd(col, " ", 1);
	ft_putstrc_fd(col, p_id, 1);
	free(p_id);
	ft_putstrc_fd(col, " ", 1);
	ft_putendlc_fd(col, act, 1);
	pthread_mutex_unlock(&data->mut_write);
}
