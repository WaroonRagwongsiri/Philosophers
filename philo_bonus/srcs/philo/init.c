/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:34:10 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/22 11:12:40 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_table(t_table *table, int argc, char **argv)
{
	table->n_philo = ft_atol(argv[1]);
	table->t_die = ft_atol(argv[2]);
	table->t_eat = ft_atol(argv[3]);
	table->t_sleep = ft_atol(argv[4]);
	table->n_eat_end = -1;
	if (argc == 6)
		table->n_eat_end = ft_atol(argv[5]);
	if (init_semaphore(&table->all_sem, table) == false)
		return (false);
	return (true);
}

bool	init_semaphore(t_semaphore *semaphore, t_table *table)
{
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_N_EAT);
	sem_unlink(SEM_MEAL);
	semaphore->stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	if (semaphore->stop == SEM_FAILED)
		return (false);
	semaphore->fork = sem_open(SEM_FORK, O_CREAT, 0644, table->n_philo);
	if (semaphore->fork == SEM_FAILED)
		return (sem_close(semaphore->stop), false);
	semaphore->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (semaphore->print == SEM_FAILED)
		return (sem_close(semaphore->stop), sem_close(semaphore->fork),
			false);
	semaphore->n_eat = sem_open(SEM_N_EAT, O_CREAT, 0644, 0);	
	if (semaphore->n_eat == SEM_FAILED)
		return (sem_close(semaphore->stop), sem_close(semaphore->fork),
			sem_close(semaphore->print), false);
	semaphore->last_meal = sem_open(SEM_MEAL, O_CREAT, 0644, table->n_philo);	
	if (semaphore->last_meal == SEM_FAILED)
		return (sem_close(semaphore->stop), sem_close(semaphore->fork),
			sem_close(semaphore->print), sem_close(semaphore->n_eat),
			false);
	return (true);
}

bool	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (table->philos == NULL)
		return (false);
	i = -1;
	while (++i < table->n_philo)
	{
		table->philos[i].pid = 0;
		table->philos[i].index = i;
		table->philos[i].t_die = table->t_die;
		table->philos[i].t_eat = table->t_eat;
		table->philos[i].t_sleep = table->t_sleep;
		table->philos[i].eat_count = 0;
		table->philos[i].last_time_eat = get_time_in_ms();
		table->philos[i].table = table;
		table->philos[i].all_sem = &table->all_sem;
	}
	return (true);
}
