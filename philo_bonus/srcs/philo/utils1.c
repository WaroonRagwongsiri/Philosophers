/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:38:52 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/21 14:39:40 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clear_sem(t_table *table)
{
	sem_close(table->all_sem.stop);
	sem_close(table->all_sem.fork);
	sem_close(table->all_sem.print);
	sem_close(table->all_sem.n_eat);
}

void	clear_table(t_table *table)
{
	free(table->philos);
	clear_sem(table);
}

void	unlink_sem()
{
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_N_EAT);
}
