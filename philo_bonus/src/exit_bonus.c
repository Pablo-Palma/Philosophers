/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/20 10:04:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	messages_died(const char *status, t_philo *philo)
{
	u_int64_t	time;

	time = get_time() - philo->table->start_time;
	if (ft_strcmp(status, END) == 0)
		printf("%llu %s\n", time, status);
	else if (philo->table->sim_end == 1 && ft_strcmp(status, DIED) == 0)
	{
		printf("%llu %d %s\n", time, philo->id, status);
		sem_wait(philo->table->sim_end_sem);
		philo->table->sim_end = 2;
		sem_post(philo->table->sim_end_sem);
	}
}

void	close_sem(t_table *table)
{
	if (table->total_meals_sem)
	{
		sem_close(table->total_meals_sem);
		sem_unlink(MEALS_SEM);
	}
	if (table->sim_end_sem)
	{
		sem_close(table->sim_end_sem);
		sem_unlink(SIM_END_SEM);
	}
}

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
	close_sem(table);
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
