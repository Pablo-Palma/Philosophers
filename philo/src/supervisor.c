/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:46:21 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/19 13:35:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(const char *status, t_philo *philo)
{
	u_int64_t	time;
	u_int64_t	start_time;
	u_int64_t	time_spent;

	start_time = get_time();
	pthread_mutex_lock(&philo->table->writex);
	pthread_mutex_lock(philo->table->sim_end_mutex);
	time = get_time() - philo->table->start_time;
	if (!philo->table->sim_end || ft_strcmp(status, DIED) == 0)
		printf("%llu %d %s\n", time, philo->id, status);
	if (ft_strcmp(status, END) == 0)
		printf("%llu %s\n", time, status);
	pthread_mutex_unlock(philo->table->sim_end_mutex);
	pthread_mutex_unlock(&philo->table->writex);
	pthread_mutex_lock(&philo->m_latency);
	time_spent = get_time() - start_time;
	philo->latency += time_spent;
	pthread_mutex_unlock(&philo->m_latency);
}

int	check_death(t_philo	*philo)
{
	u_int64_t	current_time;

	current_time = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->m_latency);
	pthread_mutex_lock(philo->statex);
	if (current_time - philo->last_meal_time
		> (u_int64_t)philo->table->tt_die + philo->latency)
	{
		pthread_mutex_unlock(&philo->m_latency);
		pthread_mutex_unlock(philo->statex);
		pthread_mutex_lock(philo->table->sim_end_mutex);
		if (!philo->table->sim_end)
		{
			philo->table->sim_end = 1;
			messages(DIED, philo);
		}
		else
			pthread_mutex_unlock(philo->table->sim_end_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->statex);
		pthread_mutex_unlock(&philo->m_latency);
	}
	return (0);
}

int	check_max_meals(t_table *table)
{
	pthread_mutex_lock(&table->meals_mutex);
	pthread_mutex_lock(table->sim_end_mutex);
	if (!table->sim_end && table->tm_eat && table->total_meals
		>= table->n_philo * table->tm_eat)
	{
		table->sim_end = 1;
		pthread_mutex_unlock(&table->meals_mutex);
		pthread_mutex_unlock(table->sim_end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->meals_mutex);
	pthread_mutex_unlock(table->sim_end_mutex);
	return (0);
}

void	*supervisor(void *arg)
{
	t_table		*table;
	int			i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->n_philo)
		{
			if (check_death(&table->philos[i]))
				return (NULL);
			i++;
		}
		if (check_max_meals(table))
		{
			messages(END, &table->philos[i - 1]);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
