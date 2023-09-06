/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:24:09 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/06 21:24:14 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_is_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static size_t	count_dec(int n)
{
	size_t	count;

	count = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*a;
	size_t		count;
	size_t		aux;
	long int	long_n;

	long_n = (long int)n;
	if (ft_is_neg(n) == 1)
		long_n = long_n * -1;
	count = count_dec(n) + ft_is_neg(n);
	aux = count;
	a = (char *)malloc(sizeof(char) * count + 2);
	if (!a)
		return (NULL);
	while (long_n / 10 != 0)
	{
		a[count--] = long_n % 10 + '0';
		long_n = long_n / 10;
	}
	a[count] = long_n % 10 + '0';
	a[aux + 1] = '\0';
	if (ft_is_neg(n) == 1)
		a[0] = '-';
	return (a);
}
