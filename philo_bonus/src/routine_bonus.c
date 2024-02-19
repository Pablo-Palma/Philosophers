/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:31:31 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/19 17:16:32 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->monitor_active)
	{
		if ((get_time() - philo->table->start_time - philo->last_meal_time)
			> ((u_int64_t)philo->table->tt_die))
		{
			messages(DIED, philo);
			exit(TIME_OUT);
		}
		opt_sleep(1, *philo);
	}
	return (NULL);
}

void	messages(const char *status, t_philo *philo)
{
	u_int64_t	time;

	sem_wait(philo->table->writex);
	time = get_time() - philo->table->start_time;
	if (!philo->table->sim_end || ft_strcmp(status, DIED) == 0)
		printf("%llu %d %s\n", time, philo->id, status);
	sem_post(philo->table->writex);
}

void	take_forks(t_philo *philo)
{
	pthread_t	monitor;

	philo->monitor_active = 1;
	pthread_create(&monitor, NULL, death_monitor, philo);
	sem_wait(philo->table->forks);
	messages(TAKE_FORKS, philo);
	sem_wait(philo->table->forks);
	messages(TAKE_FORKS, philo);
	philo->monitor_active = 0;
	pthread_join(monitor, NULL);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->last_meal_time = get_time() - philo->table->start_time;
	philo->n_meals++;
	if (!philo->table->sim_end)
		messages(EATING, philo);
	opt_sleep(philo->table->tt_eat, *philo);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	handle_single_philo(t_philo *philo)
{
	messages(TAKE_FORKS, philo);
	opt_sleep(philo->table->tt_die, *philo);
	messages(DIED, philo);
	exit(0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->n_philo == 1)
		handle_single_philo(philo);
	while (1)
	{
		eat(philo);
		if (philo->table->tm_eat > 0 && philo->n_meals >= philo->table->tm_eat)
			exit(MAX_MEALS);
		messages(SLEEPING, philo);
		opt_sleep(philo->table->tt_sleep, *philo);
		messages(THINKING, philo);
	}
}
