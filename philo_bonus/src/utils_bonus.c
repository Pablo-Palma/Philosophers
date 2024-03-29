/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:46:45 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/20 09:47:28 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	messages(const char *status, t_philo *philo)
{
	u_int64_t	time;

	sem_wait(philo->table->writex);
	time = get_time() - philo->table->start_time;
	if (!philo->table->sim_end && ft_strcmp(status, DIED) != 0)
		printf("%llu %d %s\n", time, philo->id, status);
	sem_post(philo->table->writex);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	is_numeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
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
	if (!is_numeric(argv[1]) || !is_numeric(argv[2]) || !is_numeric(argv[2])
		|| !is_numeric(argv[4]))
	{
		printf("Error: All arguments must be numeric.\n");
		return (1);
	}
	if (assign_values(table, argv, argc))
		return (1);
	if (table->n_philo <= 0 || table->tt_die <= 0 || table->tt_eat <= 0
		|| table->tt_sleep <= 0 || (argc == 6 && table->tm_eat <= 0))
	{
		printf("Error, all arguments must be positive integers");
		return (1);
	}
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
