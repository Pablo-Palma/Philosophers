/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:50:49 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/15 17:05:46 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	assign_values(t_table *table, char **argv)
{
	table->n_philo = ft_atoi(argv[1]);
	table->tt_die = ft_atoi(argv[2]);
	table->tt_eat = ft_atoi(argv[3]);
	table->tt_sleep = ft_atoi(argv[4]);
	table->start_time = 0;
	table->sim_end = 0;
}

int	init_forks(t_table *table)
{
	sem_unlink(FORKS_SEM);
	table->forks = sem_open(FORKS_SEM, O_CREAT | O_EXCL, 0644, table->n_philo);
	if (table->forks == SEM_FAILED)
	{
		write(2, "Sem_open failed", 16);
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

int	init_sems(t_table	*table)
{
	sem_unlink(WRITEX_SEM);
	table->writex = sem_open(WRITEX_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (table->writex == SEM_FAILED)
	{
		write(2, "sem_open failed for writex", 27);
		free(table->philos);
		return (0);
	}
	sem_unlink(MEALS_SEM);
	table->total_meals_sem = sem_open(MEALS_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (table->total_meals_sem == SEM_FAILED)
	{
		write(2, "sem_open failed for total_meals_sem", 27);
		free(table->philos);
		return (0);
	}
	return (1);
}

int	init_simulation(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (0);
	if (!init_forks(table) || !init_sems(table))
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
