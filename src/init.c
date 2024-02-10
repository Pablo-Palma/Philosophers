/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:50:49 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/09 14:28:45 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (0);
	while (i < table->n_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	return (1);
}

int	init_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].n_meals = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(i + 1) % table->n_philo];
		table->philos[i].table = table;
		table->philos[i].statex = malloc(sizeof(pthread_mutex_t));
		if (table->philos[i].statex == NULL)
			return (0);
		pthread_mutex_init(table->philos[i].statex, NULL);
		table->philos[i].id_thread = malloc(sizeof(pthread_t));
		if (table->philos[i].id_thread == NULL)
		{
			free(table->philos[i].statex);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_simulation(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	table->sim_end_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->sim_end_mutex)
	{
		free(table->sim_end_mutex);
		return (0);
	}
	pthread_mutex_init(table->sim_end_mutex, NULL);
	if (!table->philos)
		return (0);
	if (!init_forks(table) || !init_philosophers(table))
		return (0);
	return (1);
}
