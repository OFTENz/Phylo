/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:05 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/17 20:49:46 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	this function is checkign if the philo ate enough 
//	or if he should die cuz he spent to much time without eating 
//	and checking if he is currently eating to avoid mistaking in it's state !

int	check_philo_status(t_philo *philo)
{
	int		is_eating;
	t_data	*data;

	data = (*philo).data;
	pthread_mutex_lock(&(*philo).is_eating_mutex);
	is_eating = (*philo).is_eating;
	pthread_mutex_unlock(&(*philo).is_eating_mutex);
	pthread_mutex_lock(&(*philo).meal_time_mutex);
	if ((*data).fifth_arg && (*philo).meals >= (*data).meal_number)
		return (pthread_mutex_unlock(&(*philo).meal_time_mutex), 1);
	if (check_starved(philo, is_eating))
		return (-1);
	pthread_mutex_unlock(&(*philo).meal_time_mutex);
	return (0);
}

int	check_starved(t_philo *philo, int is_eating)
{
	t_data	*data;

	data = (*philo).data;
	if (what_timeizit()
		> ((*data).die_time + (*philo).last_meal) && is_eating != 1)
	{
		pthread_mutex_unlock(&(*philo).meal_time_mutex);
		return (write_status("died", philo), -1);
	}
	return (0);
}

//	this function is checking if the philo is dead 
//	and if he should be out of the stimulation cuz he ate enough !

int	check_all_philos(t_philo *philo, int *finished)
{
	t_data	*data;
	int		status;
	int		i;

	*finished = 0;
	data = (*philo).data;
	i = 0;
	while (i < (*data).philos_number)
	{
		status = check_philo_status(philo);
		if (status == -1)
			return (-1);
		if (status == 1)
			(*finished)++;
		philo = (*philo).next;
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*rn;
	int		belly_full;
	t_data	*data;

	rn = (t_philo *)arg;
	data = (*rn).data;
	usleep(1000);
	while (!is_dead(rn))
	{
		if (check_all_philos(rn, &belly_full) == -1)
			return (NULL);
		if (belly_full == (*data).philos_number)
		{
			pthread_mutex_lock(&(*data).death);
			(*data).all_ate = 1;
			pthread_mutex_unlock(&(*data).death);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
