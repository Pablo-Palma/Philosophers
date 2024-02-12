/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:46:21 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 11:44:51 by pabpalma         ###   ########.fr       */
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
			messages(DIED, philo);
		}
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
	while (1)
	{
		sem_wait(philo->mutex_)
	}
	return (NULL);
}