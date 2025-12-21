/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:00:05 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/21 14:55:06 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_table *table)
{
	int	philo_created;

	philo_created = create_philo_process(table);
	wait_philo(table, philo_created);
	kill_philo(table, philo_created);
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
		waitpid(table->philos[i].pid, NULL, WNOHANG);
	}
	
void	kill_philo(t_table *table, int philo_created)
{
	int	i;

	i = -1;
	while (++i < philo_created)
		kill(table->philos[i].pid, SIGKILL);	
}
