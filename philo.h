/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:08:22 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 21:51:37 by sel-mir          ###   ########.fr       */
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

typedef struct s_gcollct
{
	void				*ptr;
	struct s_gcollct	*next;
}	t_gcollct;

# define FREE_ONE 1

# define FREE_ALL 9


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

t_philo	*ft_lst_new(int data);
t_philo	*ft_lstlast(t_philo *lst);
t_philo	*create_philosophers(t_data *info, int total);
t_data	*init_mutex(t_data *info);


void	load_it(t_data *data, int i, int value);
void	wipe_all(t_gcollct *head);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	search_gcollct(t_gcollct *head, void *ptr, t_gcollct **ret);
void	*monitor_meal_limit(void *arg);
void	ft_free(void *ptr, int flag);
void	join_threads(t_philo *philo, int size);
void	eat(t_philo *philosopher);
void	print_philo_status(const char *message, t_philo *philosopher);
void	*philosopher_routine(void *arg);
void	free_one(t_gcollct **hold, t_gcollct *head, void *ptr);
void	join_threads(t_philo *philo, int size);
void	*philosopher_routine(void *arg);
void	clean_all_mutex(t_philo *philo, int count);
void	*ft_malloc(size_t size);

long	hybrid_atoi(const char *str);
long	current_time(void);

int		ft_lstadd_back(t_philo **first, t_philo *new);
int		check_if_valid(char *arg, t_data **data);
int		ft_usleep(long milliseconds, t_philo *philo);
int		handle_single_philosopher(t_philo *philo);
int		check_meals(t_philo *philo);
int		arg_validation(int argc, char **av, t_data **data);
int		initialize_philo(t_philo *philo, int size);
int		start_philosophers(t_philo *philo, int size);
int		is_dead(t_philo *philo);
int		single_mutex_init(t_philo *philo);
int		iss_digit(const char *str);

#endif