/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:54 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/16 19:56:27 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

t_data	*general_mutexe_init(t_data *data)
{
	if (pthread_mutex_init(&(*data).printing, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&(*data).death, NULL) != 0)
		return (pthread_mutex_destroy(&(*data).printing), NULL);
	if (pthread_mutex_init(&(*data).meal_count, NULL) != 0)
	{
		return (pthread_mutex_destroy(&(*data).printing),
			pthread_mutex_destroy(&(*data).death), NULL);
	}
	return (data);
}

int	philo_management(t_philo *philo)
{
	int			i;
	pthread_t	monitor;
	t_philo		*head;
	t_data	*data;

	head = philo;
	data = (*philo).data;
	if (philo_spawn(philo))
		return (1);
	if (pthread_create(&monitor, NULL, monitoring, head))
		return (join_threads(head), 1);
	pthread_join(monitor, NULL);
	i = 0;
	philo = head;
	while (i < (*data).philos_number)
	{
		pthread_join((*philo).thread, NULL);
		philo = (*philo).next;
		i++;
	}
	return (0);
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
		if (pthread_create(&((*philo).thread), NULL, philosopher_routine, philo))
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
