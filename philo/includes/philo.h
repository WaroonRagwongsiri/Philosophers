/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:13:08 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/10 22:09:59 by waroonwork@      ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_philo
{
	int				index;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_count;
	long			last_time_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat_end;
	int				*fork_arr;
	t_philo			*philo_arr;
	pthread_t		*thread;
	pthread_mutex_t	mutex;
}	t_table;

// Init
void	init_table(t_table *table, int argc, char **argv);
void	init_philo(t_table *table);
int		init_thread(t_table *table);

// Philo life
void	*philo_life(void *arg);

// Utils
long	ft_atol(const char *nptr);
long	get_time_in_ms(void);
void	end_thread(t_table *table, int th_created);
void	free_table(t_table *table);

#endif