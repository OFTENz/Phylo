/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:28 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/17 20:48:53 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_dead(t_philo *philo)
{
	t_data	*data;

	data = (*philo).data;
	pthread_mutex_lock(&(*data).death);
	if ((*data).died)
		return (pthread_mutex_unlock(&(*data).death), 1);
	return (pthread_mutex_unlock(&(*data).death), 0);
}

int	compare(char *str, char *src)
{
	int	a;

	a = 0;
	while (str[a] && src[a])
	{
		if (str[a] != src[a])
			return (1);
		a++;
	}
	if (str[a] != src[a])
		return (1);
	return (0);
}

void	write_status(char *state, t_philo *philo)
{
	t_data		*data;
	long		yet_time;

	data = (*philo).data;
	pthread_mutex_lock(&((*data).printing));
	if (is_dead(philo))
		return (pthread_mutex_unlock(&((*data).printing)), (void)1);
	if (state && !compare(state, "died"))
	{
		pthread_mutex_lock(&(*data).death);
		(*data).died = 1;
		pthread_mutex_unlock(&(*data).death);
	}
	yet_time = what_timeizit() - (*data).start;
	printf("%ld %d %s\n", yet_time, (*philo).id, state);
	pthread_mutex_unlock(&((*data).printing));
}

int	ft_usleep(long milliseconds, t_philo *philo)
{
	unsigned long	start;

	start = what_timeizit();
	while ((what_timeizit() - start) < (unsigned long)milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(500);
	}
	return (0);
}

void	*philo_activity(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (*philo).data;
	pthread_mutex_lock(&(*philo).meal_time_mutex);
	(*philo).last_meal = what_timeizit();
	pthread_mutex_unlock(&(*philo).meal_time_mutex);
	if ((*philo).id % 2 == 0)
		usleep(100);
	while (!is_dead(philo))
	{
		eat_management(philo);
		if (is_dead(philo) || satisfied_yet(philo))
			break ;
		write_status("is sleeping", philo);
		ft_usleep((*data).sleep_time, philo);
		if (is_dead(philo))
			break ;
		write_status("is thinking", philo);
	}
	return (NULL);
}
