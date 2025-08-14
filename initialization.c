/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:42:42 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 14:14:25 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_mutex(t_data *info)
{
	if (pthread_mutex_init(&info->print, NULL) != 0)
	{
		free(info);
		return (NULL);
	}
	if (pthread_mutex_init(&info->death, NULL) != 0)
	{
		pthread_mutex_destroy(&info->print);
		free(info);
		return (NULL);
	}
	if (pthread_mutex_init(&info->meal_count, NULL) != 0)
	{
		pthread_mutex_destroy(&info->print);
		pthread_mutex_destroy(&info->death);
		free(info);
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
		return (FAILURE);
	if (pthread_create(&monitor, NULL, monitor_meal_limit, head))
	{
		join_threads(head, size);
		return (FAILURE);
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
	return (SUCCESS);
}

long	calculate_thinking_time(long eat, long sleep)
{
	if (eat > sleep)
		return (eat - sleep);
	return (0);
}

t_data	*set_info(int ac, char **av)
{
	t_data	*info;

	info = malloc(sizeof(t_data));
	if (!info)
		return (NULL);
	info = init_mutex(info);
	if (!info)
		return (NULL);
	info->philos_number = hybrid_atoi(av[1]);
	info->die_time = hybrid_atoi(av[2]);
	info->eat_time = hybrid_atoi(av[3]);
	info->sleep_time = hybrid_atoi(av[4]);
	info->fifth_arg = 0;
	info->died = 0;
	info->all_ate = 0;
	if (ac > 5)
	{
		info->meal_number = hybrid_atoi(av[5]);
		info->fifth_arg = 1;
	}
	info->think_time = calculate_thinking_time(
			info->eat_time, info->sleep_time);
	info->start = current_time();
	return (info);
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
		{
			join_threads(head, i);
			return (FAILURE);
		}
		philo = philo->next;
		i++;
	}
	return (SUCCESS);
}
