/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:54:59 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/13 21:26:41 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", get_time_in_ms(), philo->index, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

bool	should_stop(t_philo *philo, t_table *table)
{
	bool	stop;

	stop = false;
	pthread_mutex_lock(&table->mutex);
	if (table->philo_died || table->philo_eat_count >= table->n_philo)
		stop = true;
	pthread_mutex_unlock(&table->mutex);
	if (get_time_in_ms() - philo->last_time_eat >= philo->t_die)
	{
		pthread_mutex_lock(&table->mutex);
		if (!table->philo_died)
		{
			table->philo_died = true;
			print_status(philo, "died");
		}
		pthread_mutex_unlock(&table->mutex);
		stop = true;
	}
	return (stop);
}

bool	should_give_fork(t_table *table, int index)
{
	long	my_last_eat;
	long	left_last_eat;
	long	right_last_eat;
	int		left;
	int		right;

	my_last_eat = table->philo_arr[index].last_time_eat;
	left = (index - 1 + table->n_philo) % table->n_philo;
	right = (index + 1) % table->n_philo;
	left_last_eat = table->philo_arr[left].last_time_eat;
	right_last_eat = table->philo_arr[right].last_time_eat;
	if (left_last_eat < my_last_eat || right_last_eat < my_last_eat)
		return (true);
	return (false);
}
