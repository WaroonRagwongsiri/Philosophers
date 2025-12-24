/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:09:07 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/24 18:17:41 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	validate_parser(int argc, char **argv)
{
	if (!validate_parser_num(argc, argv))
		return (false);
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

bool	validate_parser_num(int argc, char **argv)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (++i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len > 6)
			return (false);
		j = 0;
		while ((argv[i][j] >= '\t' && argv[i][j] <= '\r') || argv[i][j] == ' ')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				if (all_space(&argv[i][j]))
					return (true);
				return (false);
			}
			j++;
		}
	}
	return (true);
}

bool	all_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
			return (false);
		++i;
	}
	return (true);
}
