/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:42:42 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 21:37:15 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_mutex(t_data *info)
{
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&info->death, NULL) != 0)
		return (pthread_mutex_destroy(&info->print), NULL);
	if (pthread_mutex_init(&info->meal_count, NULL) != 0)
	{
		pthread_mutex_destroy(&info->print);
		pthread_mutex_destroy(&info->death);
		return (NULL);
	}
	return (info);
}

int	initialize_philo(t_philo *philo, int size)
{
	int			i;
	pthread_t	monitor;
	t_philo		*head;

	head = philo;
	if (start_philosophers(philo, size))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_meal_limit, head))
	{
		join_threads(head, size);
		return (1);
	}
	pthread_join(monitor, NULL);
	i = 0;
	philo = head;
	while (i < size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	} 
	return (0);
}
int	start_philosophers(t_philo *philo, int size)
{
	int		i;
	t_philo	*head;

	head = philo;
	i = 0;
	while (i < size)
	{
		if (pthread_create(&(philo->thread), NULL, philosopher_routine, philo))
			return (join_threads(head, i), 1);
		philo = philo->next;
		i++;
	}
	return (0);
}
