/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:15:42 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/16 19:35:51 by sel-mir          ###   ########.fr       */
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
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	is_eating_mutex;
	int				is_eating;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_data			*data;
}	t_philo;

t_philo	*new_fella(int content);
t_philo	*ft_lstlast(t_philo *lst);
t_data	*general_mutexe_init(t_data *data);


void	load_it(t_data *data, int i, int value);
void	wipe_all(t_gcollct *head);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	search_gcollct(t_gcollct *head, void *ptr, t_gcollct **ret);
void	*monitoring(void *arg);
void	ft_free(void *ptr, int flag);
void	write_status(char *state, t_philo *philo);
void	*philosopher_routine(void *arg);
void	free_one(t_gcollct **hold, t_gcollct *head, void *ptr);
void	join_threads(t_philo *philo);
void	single_mutex_destroy(t_philo *new);
void	eat_management(t_philo *philosopher);
void	*philosopher_routine(void *arg);
void	clean_all_mutex(t_philo *philo, int count);
void	*ft_malloc(size_t size);
void	join_yet(t_philo *head, int yet);
void	eat_activity(t_philo *philosopher);

long	hybrid_atoi(const char *str);
long	what_timeizit(void);

int		satisfied_yet(t_philo *philo);
int		bag_prepa(t_data *data, t_philo **headd);
int		philo_management(t_philo *philo);
int		ft_lstadd_back(t_philo **first, t_philo *new);
int		check_if_valid(char *arg, t_data **data);
int		compare(char *str, char *src);
int		ft_usleep(long milliseconds, t_philo *philo);
int		handle_single_philosopher(t_philo *philo);
int		arg_validation(int argc, char **av, t_data **data);
int		philo_spawn(t_philo *philo);
int		is_dead(t_philo *philo);
int		single_mutex_init(t_philo *philo);
int		iss_digit(const char *str);

#endif