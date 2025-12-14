/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:47:44 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/14 21:53:48 by waragwon         ###   ########.fr       */
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
	if (ft_atol(argv[1]) < 0 || ft_atol(argv[2]) < 0 || ft_atol(argv[3]) < 0
		|| ft_atol(argv[4]) < 0)
		return (false);
	if (ft_atol(argv[1]) > INT_MAX || ft_atol(argv[2]) > INT_MAX
		|| ft_atol(argv[3]) > INT_MAX || ft_atol(argv[4]) > INT_MAX)
		return (false);
	if (argc == 6 && ft_atol(argv[5]) < 1)
		return (false);
	if (argc == 6 && ft_atol(argv[5]) > INT_MAX)
		return (false);
	return (true);
}
