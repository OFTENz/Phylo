/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:48 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/16 22:21:18 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

//	This is the function that update the state of the philo to the eating state
//	protecting the 

void	update_state(t_philo *philo)
{
	pthread_mutex_lock(&(*philo).is_eating_mutex);
	(*philo).is_eating = 1;
	pthread_mutex_unlock(&(*philo).is_eating_mutex);
	pthread_mutex_lock(&(*philo).meal_time_mutex);
	(*philo).last_meal = what_timeizit();
	pthread_mutex_unlock(&(*philo).meal_time_mutex);
}

void	mo_more_eating(t_philo *philo)
{
	pthread_mutex_lock(&(*philo).is_eating_mutex);
	(*philo).is_eating = 0;
	pthread_mutex_unlock(&(*philo).is_eating_mutex);
}

void	eat_activity(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	write_status("took a fork !", philo);
	write_status("is eating !", philo);
	update_state(philo);
	ft_usleep((*data).eat_time, philo);
	pthread_mutex_lock(&(*philo).meal_time_mutex);
	(*philo).meals++;
	pthread_mutex_unlock(&(*philo).meal_time_mutex);
	pthread_mutex_unlock(&((*(*philo).next).fork));
	pthread_mutex_unlock(&((*philo).fork));
	mo_more_eating(philo);
}

void	one_philo_case(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	ft_usleep((*data).die_time, philo);
	write_status("Died", philo);
	pthread_mutex_unlock(&((*philo).fork));
	return ;	
}

void	eat_management(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	pthread_mutex_lock(&((*philo).fork));
	if (is_dead(philo))
		return (pthread_mutex_unlock(&((*philo).fork)), (void)1);
	write_status("took a fork !", philo);
	if ((*data).philos_number == 1)
		return (one_philo_case(philo), (void)1);
	pthread_mutex_lock(&((*(*philo).next).fork));
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&((*(*philo).next).fork));
		pthread_mutex_unlock(&((*philo).fork));
		return ;
	}
	eat_activity(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (*philo).data;
	pthread_mutex_lock(&(*philo).meal_time_mutex);
	(*philo).last_meal = what_timeizit();
	pthread_mutex_unlock(&(*philo).meal_time_mutex);
	if ((*philo).id % 2 == 0)
		usleep(70);
	while (!is_dead(philo))
	{
		eat_management(philo);
		if (is_dead(philo))
			break ;
		if (satisfied_yet(philo))
			break ;
		write_status("is sleeping", philo);
		ft_usleep((*data).sleep_time, philo);
		if (is_dead(philo))
			break ;
		write_status("is thinking", philo);
	}
	return (NULL);
}

int	check_if_valid(char *arg, t_data **data)
{
	static	int	i;
	long	value;

	if (iss_digit(arg))
		return (write(2, "Error: not a vaild Number !\n", 44), 1);
	value = hybrid_atoi(arg);
	if (value <= 0)
		return (1);
	if ((i == 1 || i == 2 || i == 3) && value < 60)
		return (write(2, "Error: Input a value >= 60 !\n", 30), 1);
	if (i == 0 && value > 200)
		return (write(2, "Error: Input a value <= 200\n", 29),  1);
	load_it(*data, i, value);
	i++;
	return (0);
}
