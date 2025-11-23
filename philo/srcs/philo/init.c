/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:15 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/23 16:55:16 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, int argc, char **argv)
{
	table->n_philo = ft_atol(argv[1]);
	table->t_die = ft_atol(argv[2]);
	table->t_eat = ft_atol(argv[3]);
	table->t_sleep = ft_atol(argv[4]);
	table->n_eat_end = -1;
	table->thread = malloc(sizeof(pthread_t) * table->n_philo);
	table->philo_arr = malloc(sizeof(t_philo) * table->n_philo);
	table->fork_arr = malloc(sizeof(int) * table->n_philo);
	if (argc == 6)
		table->n_eat_end = ft_atol(argv[5]);
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		table->philo_arr[i].index = i;
		table->philo_arr[i].t_die = table->t_die;
		table->philo_arr[i].t_eat = table->t_eat;
		table->philo_arr[i].t_sleep = table->t_sleep;
		table->philo_arr[i].eat_count = 0;
	}
}

int	init_thread(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		if (pthread_create(&(table->thread[i])
				, NULL, philo_life, &(table->philo_arr[i])) != 0)
			return (i);
	}
	return (i);
}

void	end_thread(t_table *table, int th_created)
{
	int	i;

	i = -1;
	while (++i < th_created)
		pthread_join(table->thread[i], NULL);
}

void	free_table(t_table *table)
{
	free(table->fork_arr);
	free(table->philo_arr);
	free(table->thread);
}
