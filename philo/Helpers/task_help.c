/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:17 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/17 23:20:00 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_all_mutex(t_philo *philo, int count)
{
	t_philo	*hold;
	t_data	*data;
	int		i;

	if (!philo)
		return ;
	i = 0;
	data = (*philo).data;
	hold = philo;
	while (i < count)
	{
		pthread_mutex_destroy(&(*hold).fork);
		pthread_mutex_destroy(&(*hold).meal_time_mutex);
		pthread_mutex_destroy(&(*hold).is_eating_mutex);
		hold = (*hold).next;
		i++;
	}
	pthread_mutex_destroy(&(*data).printing);
	pthread_mutex_destroy(&(*data).death);
}

t_philo	*new_fella(int content)
{
	t_philo	*philo;

	philo = ft_malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	(*philo).id = content;
	(*philo).meals = 0;
	(*philo).next = philo;
	(*philo).prev = philo;
	return (philo);
}

long	what_timeizit(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_lstadd_back(t_philo **first, t_philo *new)
{
	t_philo	*last;

	if (*first == NULL)
	{
		*first = new;
		(*new).next = new;
		(*new).prev = new;
	}
	else
	{
		last = ft_lstlast(*first);
		(*new).next = *first;
		(*new).prev = last;
		(*last).next = new;
		(*(*first)).prev = new;
	}
	return (1);
}

int	check_if_valid(char *arg, t_data **data)
{
	static int	i;
	long		value;

	if (iss_digit(arg))
		return (write(2, "Error: not a vaild Number !\n", 29), 1);
	value = hybrid_atoi(arg);
	if (value < 0)
		return (write(2, "Error: not a vaild Number !\n", 29), 1);
	if (i == 4 && value <= 0)
		return (write(2, "Not a valid argument !\n", 24), 1);
	if ((i == 1 || i == 2 || i == 3) && value < 60)
		return (write(2, "Error: Input a value >= 60 !\n", 30), 1);
	if (i == 0 && value > 200)
		return (write(2, "Error: Input a value <= 200\n", 29), 1);
	load_it(*data, i, value);
	i++;
	return (0);
}
