/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:20:19 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/12 15:05:04 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
//NONEEDED#####################
# include <pthread.h>
# include <string.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING	"is thinking"
# define SLEEPING	"is sleeping"
# define EATING		"is eating"
# define DIED		"died"

# define FORKS_SEM		"/forks_sem"
# define WRITEX_SEM		"/writex_sem"
#define TOTAL_MEALS_SEM "/total_meals_sem"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	sem_t			*forks;
	sem_t			*writex;
	sem_t			*total_meals_sem;
	t_philo			*philos;
	long			start_time;
	int				n_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tm_eat;
	int				total_meals;
	int				sim_end;
	pid_t			parent_pid;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	long			last_meal_time;
//	sem_t			*fork_sem;
	pid_t			pid;
	t_table			*table;
}					t_philo;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  INIT                                     //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int			init_simulation(t_table *table);
int			init_forks(t_table *table);
int			init_philosophers(t_table *table);

///####   UTILS
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  UTILS                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int			parse(int argc, char **argv, t_table *table);
void		destroy_mutexes(pthread_mutex_t *forks, int n_philo);
int			ft_atoi(const char *str);
u_int64_t	get_time(void);

///###   ROUTINE
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                	ROUTINE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void		*philo_routine(void *arg);
void		messages(const char *status, t_philo *philo);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  THREADS                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void		*supervisor(void *arg);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  EXIT                                     //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void		clear_data(t_table *table);
void		ft_exit(t_table *table);
int			error(char *str, t_table *table);

#endif
