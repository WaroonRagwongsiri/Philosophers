/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:47:44 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/11 19:51:45 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	long	ans;
	int		i;
	int		neg;

	if (!nptr)
		return (0);
	i = 0;
	ans = 0;
	neg = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ans = ans * 10 + nptr[i] - '0';
		i++;
	}
	return (ans * neg);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	validate_parser(int argc, char **argv)
{
	if (ft_atol(argv[1]) < 1 || ft_atol(argv[2]) < 1 || ft_atol(argv[3]) < 1
		|| ft_atol(argv[4]) < 1)
		return (false);
	if (argc == 6 && ft_atol(argv[5]) < 1)
		return (false);
	return (true);
}
