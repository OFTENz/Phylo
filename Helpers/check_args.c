/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:41 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/15 16:24:05 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

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

int	arg_validation(int argc, char **av, t_data **data)
{
	int	i;

	*data = ft_malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc < 5 || argc > 6)
		return (write(2, "Inavlid Arguments !\n", 34), 1);
	i = 1;
	(**data).died = 0;
	(**data).all_ate = 0;
	(**data).fifth_arg = 0;
	(**data).think_time = 0;
	(**data).start = current_time();
	while (i < argc)
	{
		if (check_if_valid(av[i], data))
			return (1);
		i++;
	}
	return (0);
}

int	single_mutex_init(t_philo *philo)
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

t_philo	*bag_prepa(t_data *data)
{
	t_philo	*new;
	t_philo *head;
	int	i;
	int		yet;

	head = NULL;
	i = 1;
	yet = 0;
	while (i <= (*data).philos_number)
	{
		new = new_fella(i);
		if (!new)
			return (clean_all_mutex(head, yet), NULL);
		(*new).data = data;
		(*new).last_meal = current_time();
		if (!single_mutex_init(new))
			return (clean_all_mutex(head, yet), NULL);
		ft_lstadd_back(&head, new);
		yet++;
		i++;
	}
	return (head);
}

void	single_mutex_destroy(t_philo *new)
{
	pthread_mutex_destroy(&((*new).fork));
	pthread_mutex_destroy(&((*new).meal_mutex));
	pthread_mutex_destroy(&((*new).save_eat));
}
