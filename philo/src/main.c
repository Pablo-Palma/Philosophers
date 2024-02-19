/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/19 15:09:17 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	leaks(void)
{
	system("leaks -q philo");
}*/

int	create_philo_threads(t_table	*table)
{
	int	i;

	i = 0;
	table->philos[i].latency = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(table->philos[i].id_thread, NULL, philo_routine,
				(void *)&(table->philos[i])) != 0)
		{
			write(2, "Failed to create philosopher thread", 36);
			ft_exit(table);
			return (1);
		}
		opt_sleep(i);
		pthread_mutex_lock(&table->philos[i].m_latency);
		table->philos[i].latency += i;
		pthread_mutex_unlock(&table->philos[i].m_latency);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	supervisor_thread;
	int			i;

	i = 0;
	if (parse(argc, argv, &table) != 0)
		return (1);
	if (!init_simulation(&table))
	{
		printf("Error: init simulation");
		return (1);
	}
	table.start_time = get_time();
	create_philo_threads(&table);
	if (pthread_create(&supervisor_thread, NULL, supervisor,
			(void *)&table) != 0)
		write(2, "Failed to create supervisor thread", 35);
	while (i < table.n_philo)
	{
		pthread_join(*(table.philos[i].id_thread), NULL);
		i++;
	}
	pthread_join(supervisor_thread, NULL);
	ft_exit(&table);
	return (0);
}
