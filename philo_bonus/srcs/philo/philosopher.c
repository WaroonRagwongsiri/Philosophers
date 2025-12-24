/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:43:08 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/24 10:17:21 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*life(void *args);
static void	eat(t_philo *philo);

void	philosopher(t_table *table, int index)
{
	pthread_t	philo_th;
	t_philo		*philo;

	philo = &table->philos[index];
	sem_wait(philo->all_sem->last_meal);
	philo->last_time_eat = get_time_in_ms();
	sem_post(philo->all_sem->last_meal);
	pthread_create(&philo_th, NULL, life, philo);
	pthread_detach(philo_th);
	while (1)
	{
		sem_wait(philo->all_sem->last_meal);
		if (get_time_in_ms() - philo->last_time_eat > philo->t_die)
		{
			sem_post(philo->all_sem->last_meal);
			print_status(philo, "died");
			sem_post(philo->all_sem->stop);
			exit(1);
		}
		sem_post(philo->all_sem->last_meal);
		usleep(100);
	}
}

static void	*life(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	if (philo->index % 2 == 1)
		usleep(philo->t_eat / 2 * 1000);
	while (1)
	{
		print_status(philo, "is thinking");
		eat(philo);
		print_status(philo, "is sleeping");
		usleep(philo->t_sleep * 1000);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->all_sem->fork);
	print_status(philo, "has taken a fork");
	sem_wait(philo->all_sem->fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	sem_wait(philo->all_sem->last_meal);
	philo->last_time_eat = get_time_in_ms();
	sem_post(philo->all_sem->last_meal);
	usleep(philo->t_eat * 1000);
	sem_post(philo->all_sem->fork);
	sem_post(philo->all_sem->fork);
	philo->eat_count++;
	if (philo->eat_count == philo->table->n_eat_end)
		sem_post(philo->all_sem->n_eat);
}
