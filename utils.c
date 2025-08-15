/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:28 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/15 16:07:28 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	print_philo_status(const char *message, t_philo *philosopher)
{
	long	elapsed_time;

	pthread_mutex_lock(&(philosopher->data->print));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&(philosopher->data->print));
		return ;
	}
	if (message && *message == 'd')
	{
		pthread_mutex_lock(&philosopher->data->death);
		philosopher->data->died = 1;
		pthread_mutex_unlock(&philosopher->data->death);
	}
	elapsed_time = current_time() - philosopher->data->start;
	printf("%ld %d %s\n", elapsed_time, philosopher->id, message);
	pthread_mutex_unlock(&(philosopher->data->print));
}

int	ft_usleep(long milliseconds, t_philo *philo)
{
	unsigned long	start;

	start = current_time();
	while ((current_time() - start) < (unsigned long)milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(500);
	}
	return (0);
}

int	handle_single_philosopher(t_philo *philo)
{
	ft_usleep(philo->data->die_time, philo);
	print_philo_status("died", philo);
	return (1);
}
