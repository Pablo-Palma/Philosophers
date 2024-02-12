/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:46:45 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 10:20:36 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	messages(const char *status, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->table->writex);
	time = get_time() - philo->table->start_time;
	if (!philo->table->sim_end || strcmp(status, DIED) == 0)
		printf("%llu %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->table->writex);
}

int	parse(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s [number_of_philosophers] [time_to_die] [time_to_eat]"
			" [time_to_sleep] (optional) "
			"[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	table->n_philo = ft_atoi(argv[1]);
	table->tt_die = ft_atoi(argv[2]);
	table->tt_eat = ft_atoi(argv[3]);
	table->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->tm_eat = ft_atoi(argv[5]);
	else
		table->tm_eat = 0;
	if (table->n_philo <= 0 || table->tt_die <= 0 || table->tt_eat <= 0
		|| table->tt_sleep <= 0 || (argc == 6 && table->tm_eat <= 0))
	{
		printf("Error, all arguments must be positive integers");
		return (1);
	}
	table->start_time = 0;
	table->sim_end = 0;
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	return (sign * nb);
}
