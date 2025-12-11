/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:27 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/11 19:53:26 by waroonwork@      ###   ########.fr       */
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

	philo = (t_philo *)arg;
	philo->last_time_eat = get_time_in_ms();
	while (get_time_in_ms() - philo->last_time_eat < philo->t_die)
	{
		printf("%ld %d is thinking\n", get_time_in_ms(), philo->index);
		while (get_time_in_ms() - philo->last_time_eat < philo->t_die)
		{
			pthread_mutex_lock(&philo->table->mutex);
			if (can_eat(philo->table, philo->index))
			{
				eat(philo, philo->index);
				pthread_mutex_unlock(&philo->table->mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->table->mutex);
		}
		printf("%ld %d is sleeping\n", get_time_in_ms(), philo->index);
		usleep(philo->t_sleep * 1000);
	}
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
	long	start_time;
	long	t_eat;

	grab_fork(philo->table, philo->index);
	printf("%ld %d is eating\n", get_time_in_ms(), index);
	start_time = get_time_in_ms();
	philo->last_time_eat = start_time;
	t_eat = philo->t_eat;
	usleep(t_eat * 1000);
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
