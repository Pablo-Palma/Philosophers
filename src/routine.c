/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:31:31 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/10 17:18:38 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	messages(const char *status, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->table->writex);
	time = get_time() - philo->table->start_time;
	if (!philo->table->sim_end || strcmp(status, DIED)== 0)
		printf("%llu %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->table->writex);
}

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
	pthread_mutex_lock(philo->table->sim_end_mutex);
	if (philo->table->sim_end)
	{
	    pthread_mutex_unlock(philo->table->sim_end_mutex);
	    return ;
	}
	pthread_mutex_unlock(philo->table->sim_end_mutex);
	take_forks(philo);
	pthread_mutex_lock(philo->statex);
	philo->last_meal_time = get_time() - philo->table->start_time;
	philo->n_meals++;
	pthread_mutex_unlock(philo->statex);
	if (!philo->table->sim_end)
	    messages(EATING, philo);
	usleep(philo->table->tt_eat * 1000);
	drop_forks(philo);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(!philo->table->sim_end)
	{
		pthread_mutex_unlock(philo->table->sim_end_mutex);
		eat(philo);
		//if (philo->table->sim_end)
			//break;
		messages(SLEEPING, philo);
    	usleep(philo->table->tt_sleep * 1000);
		messages(THINKING , philo);
//	   	usleep(philo->table->tt_sleep * 1000);
	}
	return (NULL);
}
