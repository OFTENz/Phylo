/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:41 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/18 16:54:29 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	hybrid_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	arg_validation(int ac, char **av, t_data **data)
{
	int	i;

	*data = ft_malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac < 5 || ac > 6)
		return (write(2, "Inavlid Arguments !\n", 21), 1);
	i = 1;
	(**data).died = 0;
	(**data).all_ate = 0;
	(**data).fifth_arg = 0;
	(**data).think_time = 0;
	(**data).start = what_timeizit();
	while (i < ac)
	{
		if (check_if_valid(av[i], data))
			return (1);
		i++;
	}
	return (0);
}

int	single_mutex_init(t_philo *philo)
{
	if (pthread_mutex_init(&(*philo).is_eating_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&(*philo).fork, NULL))
		return (pthread_mutex_destroy(&(*philo).is_eating_mutex), 0);
	if (pthread_mutex_init(&(*philo).meal_time_mutex, NULL))
	{
		pthread_mutex_destroy(&(*philo).is_eating_mutex);
		return (pthread_mutex_destroy(&(*philo).fork), 0);
	}
	return (1);
}

int	bag_prepa(t_data *data, t_philo **headd)
{
	t_philo	*new;
	int		yet;
	int		i;

	i = 1;
	yet = 0;
	if (!(*data).philos_number)
		return (0);
	while (i <= (*data).philos_number)
	{
		new = new_fella(i);
		if (!new)
			return (clean_all_mutex(*headd, yet), 0);
		(*new).last_meal = what_timeizit();
		(*new).data = data;
		if (!single_mutex_init(new))
			return (clean_all_mutex(*headd, yet), 0);
		ft_lstadd_back(headd, new);
		i++;
		yet++;
	}
	return (1);
}

void	single_mutex_destroy(t_philo *new)
{
	pthread_mutex_destroy(&((*new).fork));
	pthread_mutex_destroy(&((*new).meal_time_mutex));
	pthread_mutex_destroy(&((*new).is_eating_mutex));
}
