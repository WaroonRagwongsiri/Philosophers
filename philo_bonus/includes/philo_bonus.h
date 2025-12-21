/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:03:04 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/21 14:46:37 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

// Msg
# define INVALID_ARG "Invalid Arguments\n"
# define ERR_INIT "Error Init\n"
# define ERR_MALLOC "Error Malloc\n"

// Sem Name
# define SEM_STOP "/stop"
# define SEM_FORK "/fork"
# define SEM_PRINT "/print"
# define SEM_N_EAT "/n_eat"

// Const
# define MAX_PHILO 10000

typedef struct s_semaphore
{
	sem_t	*fork;
	sem_t	*print;
	sem_t	*stop;
	sem_t	*n_eat;
}	t_semaphore;

typedef struct s_philo
{
	pid_t			pid;
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
	t_semaphore	all_sem;
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat_end;
	t_philo		*philos;
}	t_table;

// Simulation
void	start_simulation(t_table *table);
int	create_philo_process(t_table *table);
void	wait_philo(t_table *table, int philo_created);
void	kill_philo(t_table *table, int philo_created);

// Philosopher
void	philosopher(t_table *table);

// Initial
bool	init_table(t_table *table, int argc, char **argv);
bool	init_semaphore(t_semaphore *semaphore, int n_philo);
bool	init_philos(t_table *table);

// Philo Utils
void	clear_sem(t_table *table);
void	clear_table(t_table *table);
void	unlink_sem();

// Utils
bool	validate_parser(int argc, char **argv);
long	get_time_in_ms(void);
long	ft_atol(const char *nptr);

#endif