/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_task.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:42:16 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 13:53:57 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_info(t_data *info)
{
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->meal_count);
	free(info);
}

void	destroy_all(t_philo *philo, int count)
{
	t_philo	*current;
	t_data	*info;
	int		i;

	if (!philo)
		return ;
	i = 0;
	info = philo->info;
	while (i < count)
	{
		current = philo;
		philo = philo->next;
		pthread_mutex_destroy(&current->fork);
		pthread_mutex_destroy(&current->meal_mutex);
		pthread_mutex_destroy(&current->save_eat);
		free(current);
		i++;
	}
	cleanup_info(info);
}

t_philo	*ft_lst_new(int content)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
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

int	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
	{
		*lst = new;
		new->next = new;
		new->prev = new;
	}
	else
	{
		last = ft_lstlast(*lst);
		if (!last)
			return (0);
		new->next = *lst;
		new->prev = last;
		last->next = new;
		(*lst)->prev = new;
	}
	return (1);
}
