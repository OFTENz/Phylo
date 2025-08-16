/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:23 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/16 19:36:20 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	join_threads(t_philo *philo)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (*philo).data;
	while (i < (*data).philos_number)
	{
		pthread_join((*philo).thread, NULL);
		philo = (*philo).prev;
		i++;
	}
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	write_status("is sleeping", philo);
	ft_usleep((*data).sleep_time, philo);
}

void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	write_status("is thinking", philo);
	ft_usleep((*data).think_time, philo);
}

int	satisfied_yet(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	if ((*data).fifth_arg == 0)
		return (0);
	pthread_mutex_lock(&(*philo).meal_time_mutex);
	if ((*philo).meals >= (*data).meal_number)
		return (pthread_mutex_unlock(&(*philo).meal_time_mutex), 1);
	else
		return (pthread_mutex_unlock(&(*philo).meal_time_mutex), 0);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	return ((*lst).prev);
}
