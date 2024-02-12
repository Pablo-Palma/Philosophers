/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:31:31 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 13:03:13 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	messages(TAKE_FORKS, philo);
	sem_wait(philo->table->forks);
	messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->last_meal_time = get_time() - philo->table->start_time;
	philo->n_meals++;
	philo->table->total_meals++;
	if (!philo->table->sim_end)
		messages(EATING, philo);
	usleep(philo->table->tt_eat * 1000);
	drop_forks(philo);
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
		{
			messages(DIED, philo);
			exit(0);
		}
		eat(philo);
		messages(SLEEPING, philo);
		usleep(philo->table->tt_sleep * 1000);
		messages(THINKING, philo);
		//usleep(philo->table->tt_sleep * 1000);
	}
}
