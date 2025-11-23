/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:53:27 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/23 20:01:50 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->mutex);
	philo->fork_arr[philo->index] = 1;
	pthread_mutex_unlock(philo->mutex);
	printf("%ld %d Grab fork\n", get_time_in_ms(), philo->index);
	usleep(3);
	return (NULL);
}
