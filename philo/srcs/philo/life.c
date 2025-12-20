/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:27 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/20 21:00:01 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	can_eat(t_table *table, int index);
static void	eat(t_philo *philo);
static void	drop_fork(t_table *table, int index);
static void	philo_sleep(t_philo *philo);

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	bool	continue_simulation;

	philo = (t_philo *)arg;
	table = (t_table *) philo->table;
	continue_simulation = true;
	while (continue_simulation)
	{
		pthread_mutex_lock(&table->mutex);
		continue_simulation = !table->philo_died
			&& table->philo_eat_count < table->n_philo;
		pthread_mutex_unlock(&table->mutex);
		if (!continue_simulation || should_stop(philo, table))
			break ;
		print_status(philo, "is thinking");
		while (!can_eat(table, philo->index) && !should_stop(philo, table))
			usleep(10);
		if (should_stop(philo, table))
			break ;
		eat(philo);
		philo_sleep(philo);
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
	if (should_give_fork(table, index) || should_stop(&table->philo_arr[index], table))
		return (false);
	pthread_mutex_lock(&table->waiter);
	can = false;
	if (fork_arr[left] == 0 && fork_arr[right] == 0)
	{
		table->fork_arr[left] = 1;
		table->fork_arr[right] = 1;
		print_status(&table->philo_arr[index], "has taken a fork");
		print_status(&table->philo_arr[index], "has taken a fork");
		can = true;
	}
	pthread_mutex_unlock(&table->waiter);
	return (can);
}

static void	drop_fork(t_table *table, int index)
{
	int	left;
	int	right;

	pthread_mutex_lock(&table->waiter);
	left = index % table->n_philo;
	right = (index + 1) % table->n_philo;
	table->fork_arr[left] = 0;
	table->fork_arr[right] = 0;
	pthread_mutex_unlock(&table->waiter);
}

static void	eat(t_philo *philo)
{
	long	t_eat;

	if (should_stop(philo, philo->table))
		return ;
	print_status(philo, "is eating");
	t_eat = philo->t_eat;
	pthread_mutex_lock(&philo->philo_mutex);
	philo->eat_count++;
	philo->last_time_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->eat_count == philo->table->n_eat_end)
		philo->table->philo_eat_count++;
	pthread_mutex_unlock(&philo->table->mutex);
	usleep(t_eat * 1000);
	drop_fork(philo->table, philo->index);
}

static void	philo_sleep(t_philo *philo)
{
	if (should_stop(philo, philo->table))
		return ;
	print_status(philo, "is sleeping");
	usleep(philo->t_sleep * 1000);
}
