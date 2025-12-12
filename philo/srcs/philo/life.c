/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:27 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/12 14:05:18 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	can_eat(t_table *table, int index);
static void	eat(t_philo *philo, int index);
static void	grab_fork(t_table *table, int index);
static void	drop_fork(t_table *table, int index);
static bool	is_wait_longest(t_table *table, t_philo *philo);

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (t_table *) philo->table;
	philo->last_time_eat = get_time_in_ms();
	while (get_time_in_ms() - philo->last_time_eat < philo->t_die && table->philo_eat_count < table->n_philo)
	{
		if (table->philo_died || get_time_in_ms() - philo->last_time_eat >= philo->t_die || table->philo_eat_count == table->n_philo)
			break ;
		printf("%ld %d is thinking\n", get_time_in_ms(), philo->index);
		while (get_time_in_ms() - philo->last_time_eat < philo->t_die && table->philo_eat_count < table->n_philo)
		{
			pthread_mutex_lock(&table->mutex);
			if (can_eat(table, philo->index))
			{
				eat(philo, philo->index);
				pthread_mutex_unlock(&table->mutex);
				break ;
			}
			pthread_mutex_unlock(&table->mutex);
		}
		if (table->philo_died || get_time_in_ms() - philo->last_time_eat >= philo->t_die || table->philo_eat_count == table->n_philo)
			break ;
		printf("%ld %d is sleeping\n", get_time_in_ms(), philo->index);
		usleep(philo->t_sleep * 1000);
	}
	pthread_mutex_lock(&table->mutex);
	if (table->philo_died == false && table->philo_eat_count < table->n_philo)
	{
		printf("%ld %d died\n", get_time_in_ms(), philo->index);
		table->philo_died = true;
	}
	pthread_mutex_unlock(&table->mutex);
	return (NULL);
}

static bool	can_eat(t_table *table, int index)
{
	int		*fork_arr;
	int		left;
	int		right;

	fork_arr = table->fork_arr;
	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	if (left == right || !is_wait_longest(table, &table->philo_arr[index]))
		return (false);
	if (fork_arr[left] == 0 && fork_arr[right] == 0)
		return (true);
	return (false);
}

static void	grab_fork(t_table *table, int index)
{
	int	left;
	int	right;

	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	table->fork_arr[left] = 1;
	table->fork_arr[right] = 1;
	if (table->philo_died || table->philo_eat_count == table->n_philo)
		return ;
	printf("%ld %d has taken a fork\n", get_time_in_ms(), index);
	printf("%ld %d has taken a fork\n", get_time_in_ms(), index);
}

static void	drop_fork(t_table *table, int index)
{
	int	left;
	int	right;

	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	table->fork_arr[left] = 0;
	table->fork_arr[right] = 0;
}

static void	eat(t_philo *philo, int index)
{
	long	t_eat;

	grab_fork(philo->table, philo->index);
	if (philo->table->philo_died || philo->table->philo_eat_count == philo->table->n_philo)
		return ;
	printf("%ld %d is eating\n", get_time_in_ms(), index);
	t_eat = philo->t_eat;
	philo->eat_count++;
	if (philo->eat_count == philo->table->n_eat_end)
		philo->table->philo_eat_count++;
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
