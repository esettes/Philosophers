/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:08:34 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/12 22:09:12 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putcolor_fd(char *color, int fd)
{
	if (fd < 0)
		return ;
	while (*color)
		write(fd, color++, 1);
}

void	ft_resetcolor_fd(int fd)
{
	char	*color;

	color = "\x1b[0m";
	if (fd < 0)
		return ;
	while (*color)
		write(fd, color++, 1);
}

void	ft_putstrc_fd(char *color, char *s, int fd)
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

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write (fd, s++, 1);
	write (fd, "\n", 1);
}
