/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 15:17:49 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_table *table)
{
	if (table->forks)
	{
		sem_close(table->forks);
		sem_unlink(FORKS_SEM);

	}
	if (table->writex)
	{
		sem_close(table->writex);
		sem_unlink(WRITEX_SEM);
	}
	if (table->total_meals_sem)
	{
		sem_close(table->total_meals_sem);
		sem_unlink(TOTAL_MEALS_SEM);
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

int	error(char *str, t_table *table)
{
	printf("%s\n", str);
	if (table)
		ft_exit(table);
	return (1);
}
