/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:01:30 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/20 10:17:20 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	opt_sleep(long time, t_philo philo)
{
	long	start;

	start = get_time();
	while ((long)get_time() - start < time)
	{
		if (((get_time() - philo.table->start_time) - philo.last_meal_time)
			>= (u_int64_t)philo.table->tt_die + (philo.table->n_philo / 10))
			exit(TIME_OUT);
		usleep(50);
	}
}
