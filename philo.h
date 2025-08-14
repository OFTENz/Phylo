/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:08:22 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 14:08:41 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>


# define SUCCESS 0
# define FAILURE 1

typedef struct s_data
{
	long			start;
	int				died;
	int				all_ate;
	int				philos_number;
	long			eat_time;
	long			sleep_time;
	long			think_time;
	long			die_time;
	int				fifth_arg;
	long			meal_number;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	meal_count;
}	t_data;


typedef struct s_philo
{
	int				id;
	long			meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	save_eat;
	int				is_eating;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_data			*info;
}	t_philo;

void	destroy_all(t_philo *philo, int count);
int		ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lst_new(int data);

long	current_time(void);
t_philo	*ft_lstlast(t_philo *lst);
int		arg_validation(int argc, char **av);
long	hybrid_atoi(const char *str);
int		check_if_valid(char *arg);
int		ft_usleep(long milliseconds, t_philo *philo);

int		handle_single_philosopher(t_philo *philo);
void	eat(t_philo *philosopher);
int		check_meals(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*monitor_meal_limit(void *arg);
void	join_threads(t_philo *philo, int size);
int		arg_validation(int argc, char **av);
void	print_philo_status(const char *message, t_philo *philosopher);
void	*philosopher_routine(void *arg);
long	calculate_thinking_time(long eat, long sleep);
int		initialize_philo(t_philo *philo, int size);
void	join_threads(t_philo *philo, int size);
t_data	*set_info(int ac, char **av);
int		start_philosophers(t_philo *philo, int size);
int		is_dead(t_philo *philo);
t_philo	*create_philosophers(t_philo *philo_list, t_data *info, int total);
int		init_philo_mutexes(t_philo *philo);
void	*philosopher_routine(void *arg);
void	cleanup_info(t_data *info);
int		iss_digit(const char *str);

#endif