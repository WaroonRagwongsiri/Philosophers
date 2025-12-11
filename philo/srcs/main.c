/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:08:41 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/11 19:52:23 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		th_created;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid Arguments\n", 18), 1);
	if (!validate_parser(argc, argv))
		return (write(2, "Invalid Arguments\n", 18), 1);
	init_table(&table, argc, argv);
	if (!table.fork_arr || !table.philo_arr || !table.thread)
		return (write(2, "Error Malloc\n", 13), free_table(&table), 1);
	init_philo(&table);
	th_created = init_thread(&table);
	if (th_created != table.n_philo)
	{
		write(2, "Error Create Thread\n", 20);
		return (end_thread(&table, th_created), free_table(&table), 1);
	}
	return (end_thread(&table, th_created), free_table(&table), 0);
}
