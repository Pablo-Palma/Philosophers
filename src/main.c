/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 09:23:10 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	pthread_t supervisor_thread;
	int	i;

	i = 0;
	if (parse(argc, argv, &table) != 0)
		return(1);
	if (!init_simulation(&table))
	{
		printf("Error: init simulation");
		return (1);
	}
	table.start_time = get_time();
	while (i < table.n_philo)
	{
		if (pthread_create(table.philos[i].id_thread, NULL, philo_routine, (void *)&(table.philos[i])) != 0)
		{
			perror("Failed to create philosopher thread");
			ft_exit(&table);
			return (1);
		}
		usleep(1);
		i++;
	}
	if (pthread_create(&supervisor_thread, NULL, supervisor, (void *)&table) != 0)
		perror("Failed to create supervisor thread");
	i = 0;
	while (i < table.n_philo)
	{
		pthread_join(*(table.philos[i].id_thread), NULL);
		i++;
	}
	pthread_join(supervisor_thread, NULL);
	ft_exit(&table);
	return (0);
}
