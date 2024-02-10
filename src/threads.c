/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:46:21 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/09 18:58:11 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *arg)
{
	t_table		*table;
	int			i;
	u_int64_t	current_time;

	table = (t_table *)arg;
	while(!table->sim_end)
	{
		i = 0;
		while (i < table->n_philo && !table->sim_end)
		{
			pthread_mutex_lock(table->philos[i].statex);
			current_time = get_time() - table->start_time;
			if ((current_time - table->philos[i].last_meal_time >= (u_int64_t)table->tt_die))
			{
				pthread_mutex_lock(table->sim_end_mutex);
				table->sim_end = 1;
				printf("%llu %d died\n", current_time, table->philos[i].id);
				pthread_mutex_unlock(table->sim_end_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(table->philos[i].statex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
