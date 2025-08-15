/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:54 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/15 16:22:49 by sel-mir          ###   ########.fr       */
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

int	philo_spawn(t_philo *philo)
{
	int			i;
	pthread_t	monitor;
	t_philo		*head;
	t_data	*data;

	head = philo;
	data = (*philo).data;
	if (start_philosophers(philo))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_meal_limit, head))
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
int	start_philosophers(t_philo *philo)
{
	int		i;
	t_philo	*head;

	head = philo;
	i = 0;
	while (i < (*(*head).data).philos_number)
	{
		if (pthread_create(&(((*philo).thread)), NULL, philosopher_routine, philo))
			return (join_threads(head), 1);
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
