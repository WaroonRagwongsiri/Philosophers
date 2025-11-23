/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:08:41 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/23 16:20:03 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("Philo %d life start\n", philo->index);
	usleep(3);
	printf("Philo %d died\n", philo->index);
	return (NULL);
}

void	init_table(t_table *table, int argc, char **argv)
{
	table->n_philo = ft_atol(argv[1]);
	table->t_die = ft_atol(argv[2]);
	table->t_eat = ft_atol(argv[3]);
	table->t_sleep = ft_atol(argv[4]);
	table->n_eat_end = -1;
	table->thread = NULL;
	table->philo_arr = NULL;
	if (argc == 6)
		table->n_eat_end = ft_atol(argv[5]);
}

int	init_philo(t_table *table)
{
	int	i;

	table->philo_arr = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo_arr)
		return (1);
	i = -1;
	while (++i < table->n_philo)
	{
		table->philo_arr[i].index = i;
		table->philo_arr[i].t_die = table->t_die;
		table->philo_arr[i].t_eat = table->t_eat;
		table->philo_arr[i].t_sleep = table->t_sleep;
		table->philo_arr[i].eat_count = 0;
	}
	return (0);
}

int	init_thread(t_table *table)
{
	int	i;

	i = -1;
	table->thread = malloc(sizeof(pthread_t) * table->n_philo);
	if (!table->thread)
		return (1);
	while (++i < table->n_philo)
	{
		if (pthread_create(&(table->thread[i]), NULL, philo_life, &(table->philo_arr[i])) != 0)
			return (i);
	}
	return (i);
}

void	end_thread(t_table *table, int thread_created)
{
	int	i;

	i = -1;
	while (++i < thread_created)
		pthread_join(table->thread[i], NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		thread_created;

	if (argc != 5 && argc != 6)
	{
		write(2, "Invalid Arguments\n", 18);
		return (1);
	}
	init_table(&table, argc, argv);
	if (init_philo(&table) != 0)
	{
		write(2, "Error create table\n", 19);
		return (1);
	}
	thread_created = init_thread(&table);
	if (thread_created != table.n_philo)
	{
		free(table.philo_arr);
		end_thread(&table, thread_created);
		write(2, "Error create table\n", 19);
		return (1);
	}
	end_thread(&table, thread_created);
	free(table.philo_arr);
	free(table.thread);
	return (0);
}
