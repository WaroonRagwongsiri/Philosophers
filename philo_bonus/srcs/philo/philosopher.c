/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:43:08 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/21 22:59:29 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher(t_table *table, int index)
{
	t_philo	*philo;

	philo = &table->philos[index];
	print_status(philo, "life start");
	usleep(philo->t_die * 1000);
	print_status(philo, "died");
	sem_post(table->all_sem.stop);
	clear_table(table);
	exit(EXIT_SUCCESS);
}
