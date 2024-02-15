/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:31:31 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/15 09:20:56 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	if (!philo->table->sim_end)
		messages(TAKE_FORKS, philo);
	pthread_mutex_lock(second_fork);
	if (!philo->table->sim_end)
		messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	u_int64_t time;

	/*pthread_mutex_lock(philo->table->sim_end_mutex);
	if (philo->table->sim_end)
	{
		pthread_mutex_unlock(philo->table->sim_end_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->table->sim_end_mutex);*/
	take_forks(philo);
	pthread_mutex_lock(&philo->table->meals_mutex);
	philo->table->total_meals++;
	pthread_mutex_unlock(&philo->table->meals_mutex);
	pthread_mutex_lock(philo->table->sim_end_mutex);
	if (!philo->table->sim_end)
	{
		pthread_mutex_unlock(philo->table->sim_end_mutex);
		messages(EATING, philo);
	}
	else
		pthread_mutex_unlock(philo->table->sim_end_mutex);
	usleep(philo->table->tt_eat * 1000);
	drop_forks(philo);
	pthread_mutex_lock(philo->statex);
	time = get_time();
	philo->last_meal_time = time - philo->table->start_time;
	philo->n_meals++;
	pthread_mutex_unlock(philo->statex);
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	messages(TAKE_FORKS, philo);
	usleep(philo->table->tt_die * 1000);
//	messages(DIED, philo);
	return ;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->n_philo == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(philo->table->sim_end_mutex);
		if (philo->table->sim_end)
		{
			pthread_mutex_unlock(philo->table->sim_end_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(philo->table->sim_end_mutex);
		eat(philo);
		messages(SLEEPING, philo);
		usleep(philo->table->tt_sleep * 1000);
		messages(THINKING, philo);
	//	usleep(philo->table->tt_sleep * 1000);
	}
	return (NULL);
}
