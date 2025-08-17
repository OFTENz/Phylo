/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:54 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/17 15:31:23 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	general_mutexe_init(t_data *data)
{
	if (pthread_mutex_init(&(*data).printing, NULL))
		return (0);
	if (pthread_mutex_init(&(*data).death, NULL))
		return (pthread_mutex_destroy(&(*data).printing), 0);
	if (pthread_mutex_init(&(*data).meal_count, NULL))
	{
		return (pthread_mutex_destroy(&(*data).printing),
			pthread_mutex_destroy(&(*data).death), 0);
	}
	return (1);
}

int	philo_management(t_philo *philo)
{
	pthread_t	monitor;
	t_data	*data;

	data = (*philo).data;
	if (philo_spawn(philo))
		return (1);
	if (pthread_create(&monitor, NULL, monitoring, philo))
		return (join_threads(philo), 1);
	pthread_join(monitor, NULL);
	philosophers_join(data, philo);
	return (0);
}


void	philosophers_join(t_data *data, t_philo *head)
{
	int	i;
	
	i = 0;
	while (i < (*data).philos_number)
	{
		pthread_join((*head).thread, NULL);
		head = (*head).next;
		i++;
	}
}


int	philo_spawn(t_philo *philo)
{
	t_philo	*head;
	t_data	*data;
	int		i;

	head = philo;
	data = (*head).data;
	i = 0;
	while (i < (*data).philos_number)
	{
		if (pthread_create(&((*philo).thread), NULL, philo_routine, philo))
			return (join_yet(head, i), 1);
		philo = (*philo).next;
		i++;
	}
	return (0);
}

void	join_yet(t_philo *head, int yet)
{
	int		i;

	i = 0;
	while (i < yet)
	{
		pthread_join((*head).thread, NULL);
		head = (*head).prev;
		i++;
	}
}
