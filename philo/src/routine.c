/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:31:31 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/19 15:26:08 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	opt_sleep(long time)
{
	long	start;

	start = get_time();
	while ((long)get_time() - start < time)
		usleep(50);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	u_int64_t		start_time;
	u_int64_t		time_spent;

	start_time = get_time();
	first_fork = philo->right_fork;
	second_fork = philo->left_fork;
	pthread_mutex_lock(first_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(second_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(&philo->m_latency);
	time_spent = get_time() - start_time;
	philo->latency += time_spent;
	pthread_mutex_unlock(&philo->m_latency);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->statex);
	philo->last_meal_time = get_time() - philo->table->start_time;
	philo->n_meals++;
	pthread_mutex_unlock(philo->statex);
	pthread_mutex_lock(&philo->table->meals_mutex);
	philo->table->total_meals++;
	pthread_mutex_unlock(&philo->table->meals_mutex);
	messages(EATING, philo);
	opt_sleep(philo->table->tt_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	messages(TAKE_FORKS, philo);
	opt_sleep(philo->table->tt_die);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->n_philo == 1 && handle_single_philo(philo))
		return (NULL);
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
		if (philo->id % 2 == 0)
			opt_sleep(1);
		eat(philo);
		messages(SLEEPING, philo);
		opt_sleep(philo->table->tt_sleep);
		messages(THINKING, philo);
	}
	return (NULL);
}
