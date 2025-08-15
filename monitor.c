/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:05 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/15 16:07:05 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static int	check_philo_status(t_philo *philo)
{
	int		is_eating;

	pthread_mutex_lock(&philo->save_eat);
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->save_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->fifth_arg && philo->meals >= philo->data->meal_number)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	else if (current_time()
		> (philo->data->die_time + philo->last_meal) && is_eating != 1)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		print_philo_status("died", philo);
		return (-1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static int	check_all_philos(t_philo *philo, int *finished)
{
	int	i;
	int	status;

	*finished = 0;
	i = 0;
	while (i < philo->data->philos_number)
	{
		status = check_philo_status(philo);
		if (status == -1)
			return (-1);
		if (status == 1)
			(*finished)++;
		philo = philo->next;
		i++;
	}
	return (0);
}

void	*monitor_meal_limit(void *arg)
{
	t_philo	*current_philo;
	int		finished_philosophers;

	current_philo = (t_philo *)arg;
	usleep(1000);
	while (!is_dead(current_philo))
	{
		if (check_all_philos(current_philo, &finished_philosophers) == -1)
			return (NULL);
		if (finished_philosophers == current_philo->data->philos_number)
		{
			pthread_mutex_lock(&current_philo->data->death);
			current_philo->data->all_ate = 1;
			pthread_mutex_unlock(&current_philo->data->death);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
