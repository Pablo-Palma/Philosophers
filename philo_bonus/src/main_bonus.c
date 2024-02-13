/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:42 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/13 10:27:01 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_philo_pro(t_table	*table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid < 0)
		{
			perror("Failed to create philosopher process");
			ft_exit(table);
			return (1);
		}
		else if (table->philos[i].pid == 0)
		{
			philo_routine(&(table->philos[i]));
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

void	terminate_philos(t_table	*table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		kill(table->philos[i].pid, SIGTERM);
		i++;
	}
}

void	wait_and_terminate(t_table	*table)
{
	int		status;
	int		i;
	int		count_meals;
	pid_t	pid;

	i = 0;
	count_meals = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == MAX_MEALS)
				count_meals++;
			if (count_meals >= table->n_philo
				|| WEXITSTATUS(status) == TIME_OUT)
			{
				terminate_philos(table);
				messages(DIED, &table->philos[i]);
				break ;
			}
		}
		pid = waitpid(-1, &status, 0);
	}
	ft_exit(table);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (parse(argc, argv, &table) != 0)
		return (1);
	if (!init_simulation(&table))
	{
		printf("Error: init simulation");
		return (1);
	}
	table.start_time = get_time();
	if (create_philo_pro(&table) != 0)
		return (1);
	wait_and_terminate(&table);
	return (0);
}
