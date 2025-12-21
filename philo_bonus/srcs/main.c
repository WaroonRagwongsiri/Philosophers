/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:02:50 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/12/21 23:35:04 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (write(2, INVALID_ARG, sizeof(INVALID_ARG)), 1);
	if (!validate_parser(argc, argv))
		return (write(2, INVALID_ARG, sizeof(INVALID_ARG)), 1);
	if (init_table(&table, argc, argv) == false)
		return (write(2, ERR_INIT, sizeof(ERR_INIT)), 1);
	if (init_philos(&table) == false)
		return (write(2, ERR_MALLOC, sizeof(ERR_MALLOC)),
			clear_sem(&table.all_sem), 1);
	start_simulation(&table);
	clear_table(&table);
	return (0);
}
