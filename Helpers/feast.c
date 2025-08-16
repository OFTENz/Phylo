/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:48 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/16 19:37:09 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	eat_activity(t_philo *philosopher)
{
	t_data	*data;

	data = (*philosopher).data;
	write_status("took a fork !", philosopher);
	write_status("is eating !", philosopher);
	pthread_mutex_lock(&(*philosopher).is_eating_mutex);
	(*philosopher).is_eating = 1;
	pthread_mutex_unlock(&(*philosopher).is_eating_mutex);
	pthread_mutex_lock(&(*philosopher).meal_time_mutex);
	(*philosopher).last_meal = what_timeizit();
	pthread_mutex_unlock(&(*philosopher).meal_time_mutex);
	ft_usleep((*data).eat_time, philosopher);
	pthread_mutex_lock(&(*philosopher).meal_time_mutex);
	(*philosopher).meals++;
	pthread_mutex_unlock(&(*philosopher).meal_time_mutex);
	pthread_mutex_unlock(&((*(*philosopher).next).fork));
	pthread_mutex_unlock(&((*philosopher).fork));
	pthread_mutex_lock(&(*philosopher).is_eating_mutex);
	(*philosopher).is_eating = 0;
	pthread_mutex_unlock(&(*philosopher).is_eating_mutex);
}

void	eat_management(t_philo *philosopher)
{
	t_data	*data;

	data = (*philosopher).data;
	pthread_mutex_lock(&((*philosopher).fork));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&((*philosopher).fork));
		return ;
	}
	write_status("took a fork !", philosopher);
	if ((*data).philos_number == 1)
	{
		ft_usleep((*data).die_time, philosopher);
		write_status("Died", philosopher);
		pthread_mutex_unlock(&((*philosopher).fork));
		return ;
	}
	pthread_mutex_lock(&((*(*philosopher).next).fork));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&((*(*philosopher).next).fork));
		pthread_mutex_unlock(&((*philosopher).fork));
		return ;
	}
	eat_activity(philosopher);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
		philo_sleep(philo);
		if (is_dead(philo))
			break ;
		philo_think(philo);
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
