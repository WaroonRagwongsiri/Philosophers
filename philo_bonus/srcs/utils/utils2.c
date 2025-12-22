/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:38:52 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/22 11:13:13 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clear_sem(t_semaphore *semaphore)
{
	if (semaphore->stop != SEM_FAILED)
		sem_close(semaphore->stop);
	if (semaphore->fork != SEM_FAILED)
		sem_close(semaphore->fork);
	if (semaphore->print != SEM_FAILED)
		sem_close(semaphore->print);
	if (semaphore->n_eat != SEM_FAILED)
		sem_close(semaphore->n_eat);
	if (semaphore->last_meal != SEM_FAILED)
		sem_close(semaphore->last_meal);
}

void	clear_table(t_table *table)
{
	free(table->philos);
	clear_sem(&table->all_sem);
}

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->all_sem->print);
	printf("%ld %d %s\n", get_time_in_ms(), philo->index, status);
	sem_post(philo->all_sem->print);
}
