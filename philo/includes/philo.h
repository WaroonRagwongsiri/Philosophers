/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:13:08 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/11/23 16:16:20 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int	index;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	eat_count;
}	t_philo;

typedef struct s_table
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat_end;
	t_philo		*philo_arr;
	pthread_t	*thread;
}	t_table;

// Utils
long	ft_atol(const char *nptr);

#endif