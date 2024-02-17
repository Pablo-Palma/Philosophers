/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:31:31 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/17 13:02:01 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->table->forks);
	messages(TAKE_FORKS, philo);
	sem_wait(philo->table->forks);
	messages(TAKE_FORKS, philo);
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
	usleep(philo->table->tt_die * 1000);
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
		if ((get_time() - philo->table->start_time - philo->last_meal_time)
			> ((u_int64_t)philo->table->tt_die))
			exit(TIME_OUT);
		eat(philo);
		if ((get_time() - philo->table->start_time - philo->last_meal_time)
			> ((u_int64_t)philo->table->tt_die))
			exit(TIME_OUT);
		if (philo->table->tm_eat > 0 && philo->n_meals >= philo->table->tm_eat)
			exit(MAX_MEALS);
		messages(SLEEPING, philo);
		opt_sleep(philo->table->tt_sleep, *philo);
		messages(THINKING, philo);
	}
}
