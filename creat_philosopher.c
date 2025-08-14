/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:41:15 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 13:53:57 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philosophers(t_philo *philo_list, t_data *info, int total)
{
	t_philo	*new_philo;
	int		id;
	int		created;

	(1) && (id = 1, created = 0);
	while (id <= total)
	{
		new_philo = ft_lst_new(id);
		if (!new_philo)
			return (destroy_all(philo_list, created), NULL);
		new_philo->info = info;
		new_philo->last_meal = current_time();
		if (!init_philo_mutexes(new_philo))
			return (destroy_all(philo_list, created), free(new_philo), NULL);
		if (!ft_lstadd_back(&philo_list, new_philo))
		{
			pthread_mutex_destroy(&new_philo->fork);
			pthread_mutex_destroy(&new_philo->meal_mutex);
			pthread_mutex_destroy(&new_philo->save_eat);
			return (free(new_philo), destroy_all(philo_list, created), NULL);
		}
		created++;
		id++;
	}
	return (philo_list);
}
