/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:00:05 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/23 17:31:06 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitor_n_eat(void *args);

void	start_simulation(t_table *table)
{
	int			philo_created;
	pthread_t	monitor_thread;
	int			i;

	if (table->n_eat_end > 0)
		pthread_create(&monitor_thread, NULL, monitor_n_eat, table);
	philo_created = create_philo_process(table);
	if (philo_created != table->n_philo)
		sem_post(table->all_sem.stop);
	monitor_thread = 0;
	sem_wait(table->all_sem.stop);
	kill_philo(table, philo_created);
	i = -1;
	while (++i < table->n_philo)
		sem_post(table->all_sem.n_eat);
	wait_philo(table, philo_created);
	if (monitor_thread)
		pthread_join(monitor_thread, NULL);
}

int	create_philo_process(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (i);
		if (table->philos[i].pid == 0)
			philosopher(table, i);
	}
	return (i);
}

void	wait_philo(t_table *table, int philo_created)
{
	int	i;

	i = -1;
	while (++i < philo_created)
		waitpid(table->philos[i].pid, NULL, 0);
}

void	kill_philo(t_table *table, int philo_created)
{
	int	i;

	i = -1;
	while (++i < philo_created)
		kill(table->philos[i].pid, SIGKILL);
}

static void	*monitor_n_eat(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = -1;
	while (++i < table->n_philo)
		sem_wait(table->all_sem.n_eat);
	sem_post(table->all_sem.stop);
	return (NULL);
}
