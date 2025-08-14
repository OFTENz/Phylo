/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:30:59 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 14:22:45 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philosopher)
{
	print_philo_status("has taken a fork", philosopher);
	print_philo_status("is eating", philosopher);
	pthread_mutex_lock(&philosopher->save_eat);
	philosopher->is_eating = 1;
	pthread_mutex_unlock(&philosopher->save_eat);
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->last_meal = current_time();
	pthread_mutex_unlock(&philosopher->meal_mutex);
	ft_usleep(philosopher->info->eat_time, philosopher);
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->meals++;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	pthread_mutex_unlock(&(philosopher->next->fork));
	pthread_mutex_unlock(&(philosopher->fork));
	pthread_mutex_lock(&philosopher->save_eat);
	philosopher->is_eating = 0;
	pthread_mutex_unlock(&philosopher->save_eat);
}

void	eat(t_philo *philosopher)
{
	pthread_mutex_lock(&(philosopher->fork));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&(philosopher->fork));
		return ;
	}
	print_philo_status("has taken a fork", philosopher);
	if (philosopher->info->philos_number == 1)
	{
		ft_usleep(philosopher->info->die_time, philosopher);
		print_philo_status("died", philosopher);
		pthread_mutex_unlock(&(philosopher->fork));
		return ;
	}
	pthread_mutex_lock(&(philosopher->next->fork));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&(philosopher->next->fork));
		pthread_mutex_unlock(&(philosopher->fork));
		return ;
	}
	eating(philosopher);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
		usleep(70);
	while (!is_dead(philo))
	{
		eat(philo);
		if (is_dead(philo))
			break ;
		if (check_meals(philo))
			break ;
		philo_sleep(philo);
		if (is_dead(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
