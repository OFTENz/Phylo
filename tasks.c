/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:23 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/15 16:22:26 by sel-mir          ###   ########.fr       */
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
	print_philo_status("is sleeping", philo);
	ft_usleep(philo->data->sleep_time, philo);
}

void	philo_think(t_philo *philo)
{
	print_philo_status("is thinking", philo);
	ft_usleep(philo->data->think_time, philo);
}

int	check_meals(t_philo *philo)
{
	int	result;

	if (philo->data->fifth_arg == 0)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	result = (philo->meals >= philo->data->meal_number);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (result);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	return ((*lst).prev);
}
