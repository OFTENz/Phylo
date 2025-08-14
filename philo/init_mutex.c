/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:33:47 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 03:18:30 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->save_eat, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->save_eat);
		return (0);
	}
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->save_eat);
		pthread_mutex_destroy(&philo->fork);
		return (0);
	}
	return (1);
}
