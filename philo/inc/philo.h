/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:20:19 by pabpalma          #+#    #+#             */
/*   Updated: 2024/02/17 16:41:49 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING	"is thinking"
# define SLEEPING	"is sleeping"
# define EATING		"is eating"
# define DIED		"died"
# define END		"End of the simulation"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	writex;
	pthread_mutex_t	meals_mutex;
	t_philo			*philos;
	long			start_time;
	int				n_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tm_eat;
	int				total_meals;
	int				sim_end;
	pthread_mutex_t	*sim_end_mutex;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	u_int64_t		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*statex;
	pthread_t		*id_thread;
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
int			assign_values(t_table *table, char **argv, int argc);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  UTILS                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
int			parse(int argc, char **argv, t_table *table);
void		destroy_mutexes(pthread_mutex_t *forks, int n_philo);
int			ft_atoi(const char *str);
u_int64_t	get_time(void);
int			ft_strcmp(const char *s1, const char *s2);
int			is_numeric(const char *str);

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
int			check_death(t_philo	*philo);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  EXIT                                     //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void		clear_data(t_table *table);
void		ft_exit(t_table *table);
int			error(char *str, t_table *table);

#endif
