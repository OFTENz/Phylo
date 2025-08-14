/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:44:57 by akella            #+#    #+#             */
/*   Updated: 2025/07/25 08:45:18 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
