/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:46:21 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/13 13:48:06 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo	*philo)
{
	u_int64_t	current_time;

	pthread_mutex_lock(philo->statex);
	current_time = get_time() - philo->table->start_time;
	if ((current_time - philo->last_meal_time
			> (u_int64_t)philo->table->tt_die))
	{
		pthread_mutex_lock(philo->table->sim_end_mutex);
		if (!philo->table->sim_end)
		{
			philo->table->sim_end = 1;
			pthread_mutex_unlock(philo->table->sim_end_mutex);
			messages(DIED, philo);
		}
		else
			pthread_mutex_unlock(philo->table->sim_end_mutex);
		pthread_mutex_unlock(philo->statex);
		return (1);
	}
	pthread_mutex_unlock(philo->statex);
	return (0);
}

void	*supervisor(void *arg)
{
	t_table		*table;
	int			i;

	table = (t_table *)arg;
	while (!table->sim_end)
	{
		i = 0;
		while (i < table->n_philo && !table->sim_end)
		{
			if (check_death(&table->philos[i]))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&table->meals_mutex);
		pthread_mutex_lock(table->sim_end_mutex);
		if (!table->sim_end && table->tm_eat && table->total_meals
			>= table->n_philo * table->tm_eat)
		{
			table->sim_end = 1;
			pthread_mutex_unlock(table->sim_end_mutex);
			messages(DIED, &table->philos[i - 1]);
			pthread_mutex_unlock(&table->meals_mutex);
			break ;
		}
		pthread_mutex_unlock(table->sim_end_mutex);
		pthread_mutex_unlock(&table->meals_mutex);
		usleep(1000);
	}
	return (NULL);
}
