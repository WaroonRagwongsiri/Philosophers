/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:43:08 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/21 14:57:16 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher(t_table *table, int index)
{
	t_philo	*philo;

	philo = &table->philos[index];
	printf("%d life start\n", philo->index);
	usleep(10000);
	clear_table(table);
	exit(EXIT_SUCCESS);
}
