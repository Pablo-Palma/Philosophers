/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/13 13:36:26 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philosophers(t_table *table)
{
	int	i;

	i = 0;
	if (table->philos)
	{
		while (i < table->n_philo)
		{
			if (table->philos[i].statex)
			{
				pthread_mutex_destroy(table->philos[i].statex);
				free(table->philos[i].statex);
				table->philos[i].statex = NULL;
			}
			if (table->philos[i].id_thread)
			{
				free(table->philos[i].id_thread);
				table->philos[i].id_thread = NULL;
			}
			i++;
		}
		free(table->philos);
		table->philos = NULL;
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
		free(table->forks);
		table->forks = NULL;
	}
	i = 0;
	pthread_mutex_destroy(&table->writex);
	pthread_mutex_destroy(&table->meals_mutex);
	if (table->sim_end_mutex)
	{
		pthread_mutex_destroy(table->sim_end_mutex);
		free(table->sim_end_mutex);
		table->sim_end_mutex = NULL;
	}
	clear_philosophers(table);
}

int	error(char *str, t_table *table)
{
	printf("%s\n", str);
	if (table)
		ft_exit(table);
	return (1);
}
