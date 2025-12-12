/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:27 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/12 20:26:51 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	can_eat(t_table *table, int index);
static void	eat(t_philo *philo);
static void	drop_fork(t_table *table, int index);

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (t_table *) philo->table;
	philo->last_time_eat = get_time_in_ms();
	while (table->philo_eat_count < table->n_philo)
	{
		if (should_stop(philo, table))
			break ;
		print_status(philo, "is thinking");
		while (table->philo_eat_count < table->n_philo)
		{
			if (can_eat(table, philo->index))
				eat(philo);
			break ;
		}
		if (should_stop(philo, table))
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->t_sleep * 1000);
	}
	return (NULL);
}

static bool	can_eat(t_table *table, int index)
{
	int		*fork_arr;
	int		left;
	int		right;
	bool	can;

	fork_arr = table->fork_arr;
	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	if (left == right)
		return (false);
	if (left < right)
	{
		pthread_mutex_lock(&table->fork_mutex[left]);
		pthread_mutex_lock(&table->fork_mutex[right]);
	}
	else
	{
		pthread_mutex_lock(&table->fork_mutex[right]);
		pthread_mutex_lock(&table->fork_mutex[left]);
	}
	can = false;
	if (fork_arr[left] == 0 && fork_arr[right] == 0)
	{
		table->fork_arr[left] = 1;
		table->fork_arr[right] = 1;
		print_status(&table->philo_arr[index], "has taken a fork");
		print_status(&table->philo_arr[index], "has taken a fork");
		can = true;
	}
	pthread_mutex_unlock(&table->fork_mutex[left]);
	pthread_mutex_unlock(&table->fork_mutex[right]);
	return (can);
}

static void	drop_fork(t_table *table, int index)
{
	int	left;
	int	right;

	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	if (left < right)
	{
		pthread_mutex_lock(&table->fork_mutex[left]);
		pthread_mutex_lock(&table->fork_mutex[right]);
	}
	else
	{
		pthread_mutex_lock(&table->fork_mutex[right]);
		pthread_mutex_lock(&table->fork_mutex[left]);
	}
	table->fork_arr[left] = 0;
	table->fork_arr[right] = 0;
	pthread_mutex_unlock(&table->fork_mutex[left]);
	pthread_mutex_unlock(&table->fork_mutex[right]);
}

static void	eat(t_philo *philo)
{
	long	t_eat;

	if (should_stop(philo, philo->table))
		return ;
	print_status(philo, "is eating");
	t_eat = philo->t_eat;
	philo->eat_count++;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->eat_count == philo->table->n_eat_end)
		philo->table->philo_eat_count++;
	pthread_mutex_unlock(&philo->table->mutex);
	usleep(t_eat * 1000);
	philo->last_time_eat = get_time_in_ms();
	drop_fork(philo->table, philo->index);
}
