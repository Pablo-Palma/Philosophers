/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/09 17:45:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_table *table)
{
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
}

void	ft_exit(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(table->writex);
	pthread_mutex_destroy(table->sim_end_mutex);
	clear_data(table);
}

int	error(char *str, t_table *table)
{
	printf("%s\n", str);
	if (table)
		ft_exit(table);
	return (1);
}
