/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:27 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/12 17:13:28 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	can_eat(t_table *table, int index);
static void	eat(t_philo *philo);
static void	drop_fork(t_table *table, int index);
static bool	is_wait_longest(t_table *table, t_philo *philo);

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
	int	*fork_arr;
	int	left;
	int	right;

	fork_arr = table->fork_arr;
	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	if (left == right || !is_wait_longest(table, &table->philo_arr[index]))
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
	if (fork_arr[left] == 0 && fork_arr[right] == 0)
	{
		table->fork_arr[left] = 1;
		table->fork_arr[right] = 1;
		pthread_mutex_unlock(&table->fork_mutex[left]);
		pthread_mutex_unlock(&table->fork_mutex[right]);
		print_status(&table->philo_arr[index], "has taken a fork");
		print_status(&table->philo_arr[index], "has taken a fork");
		return (true);
	}
	pthread_mutex_unlock(&table->fork_mutex[left]);
	pthread_mutex_unlock(&table->fork_mutex[right]);
	return (false);
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

static bool	is_wait_longest(t_table *table, t_philo *philo)
{
	int		i;
	long	max_longest;

	max_longest = philo->last_time_eat;
	i = 0;
	while (i < table->n_philo)
	{
		if (philo->last_time_eat < max_longest)
			max_longest = philo->last_time_eat;
		++i;
	}
	return (max_longest == philo->last_time_eat);
}
