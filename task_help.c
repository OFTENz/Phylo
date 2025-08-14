/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:42:16 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 21:23:40 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	clean_all_mutex(t_philo *philo, int count)
{
	t_philo	*hold;
	t_data	*info;
	int		i;

	if (!philo)
		return ;
	i = 0;
	info = philo->info;
	hold = philo;
	while (i < count)
	{
		pthread_mutex_destroy(&hold->fork);
		pthread_mutex_destroy(&hold->meal_mutex);
		pthread_mutex_destroy(&hold->save_eat);
		hold = (*hold).next;
		i++;
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->meal_count);
}

t_philo	*ft_lst_new(int content)
{
	t_philo	*philo;

	philo = ft_malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = content;
	philo->meals = 0;
	philo->next = philo;
	philo->prev = philo;
	return (philo);
}

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_lstadd_back(t_philo **first, t_philo *new)
{
	t_philo	*last;

	if (!first || !new)
		return (0);
	if (*first == NULL)
	{
		*first = new;
		new->next = new;
		new->prev = new;
	}
	else
	{
		last = ft_lstlast(*first);
		new->next = *first;
		new->prev = last;
		last->next = new;
		(*first)->prev = new;
	}
	return (1);
}
