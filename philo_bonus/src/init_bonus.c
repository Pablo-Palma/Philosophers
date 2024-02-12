/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:50:49 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 12:31:08 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_forks(t_table *table)
{
	
	sem_unlink(FORKS_SEM);
	table->forks = sem_open(FORKS_SEM, O_CREAT | O_EXCL, 0644, table->n_philo);
	if (table->forks == SEM_FAILED)
	{
		perror ("Sem_open failed");
		return (0);
	}
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
		table->total_meals = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

int	init_simulation(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (0);
	sem_unlink(WRITEX_SEM);
	table->writex = sem_open(WRITEX_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (table->writex == SEM_FAILED)
	{
		perror ("sem_open failed for writex");
		free(table->philos);
		return (0);
	}
	if (!init_forks(table))
	{
		free(table->philos);
		return (0);
	}
	if (!init_philosophers(table))
	{
		sem_close(table->forks);
		sem_unlink(FORKS_SEM);
		free(table->philos);
		return (0);
	}
	return (1);
}
