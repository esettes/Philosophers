/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:19:59 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/16 19:34:53 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	count_dec(unsigned long n)
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

char	*ft_itoa(unsigned long int n)
{
	char				*a;
	size_t				count;
	size_t				aux;
	unsigned long int	long_n;

	long_n = n;
	count = count_dec(n);
	aux = count;
	a = malloc(sizeof(char) * (count + 2));
	if (!a)
		return (NULL);
	while (long_n / 10 != 0)
	{
		a[count--] = long_n % 10 + '0';
		long_n = long_n / 10;
	}
	a[count] = long_n % 10 + '0';
	a[aux + 1] = '\0';
	return (a);
}

unsigned long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	uint64_t	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		printf("res: %llu\n", res);
		if ((res * sign) > 1999 || (res * sign) < 0)
			return (1999);
		i++;
	}
	return (res * sign);
}
