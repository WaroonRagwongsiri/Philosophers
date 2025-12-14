/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:54:59 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/14 19:21:53 by waragwon         ###   ########.fr       */
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
	long	time_since_last_meal;

	stop = false;
	pthread_mutex_lock(&table->mutex);
	if (table->philo_died || table->philo_eat_count >= table->n_philo)
		stop = true;
	pthread_mutex_unlock(&table->mutex);
	if (stop)
		return (true);
	pthread_mutex_lock(&philo->philo_mutex);
	time_since_last_meal = get_time_in_ms() - philo->last_time_eat;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (time_since_last_meal >= philo->t_die)
	{
		pthread_mutex_lock(&table->mutex);
		if (!table->philo_died)
		{
			table->philo_died = true;
			print_status(philo, "died");
		}
		pthread_mutex_unlock(&table->mutex);
		return (true);
	}
	return (false);
}

bool	should_give_fork(t_table *table, int index)
{
	long	my_last_eat;
	long	left_last_eat;
	long	right_last_eat;
	int		left;
	int		right;

	pthread_mutex_lock(&table->philo_arr[index].philo_mutex);
	my_last_eat = table->philo_arr[index].last_time_eat;
	pthread_mutex_unlock(&table->philo_arr[index].philo_mutex);
	left = (index - 1 + table->n_philo) % table->n_philo;
	pthread_mutex_lock(&table->philo_arr[left].philo_mutex);
	left_last_eat = table->philo_arr[left].last_time_eat;
	pthread_mutex_unlock(&table->philo_arr[left].philo_mutex);
	right = (index + 1) % table->n_philo;
	pthread_mutex_lock(&table->philo_arr[right].philo_mutex);
	right_last_eat = table->philo_arr[right].last_time_eat;
	pthread_mutex_unlock(&table->philo_arr[right].philo_mutex);
	return (left_last_eat < my_last_eat || right_last_eat < my_last_eat);
}
