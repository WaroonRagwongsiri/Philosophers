/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:54:59 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/12 17:02:04 by waroonwork@      ###   ########.fr       */
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
