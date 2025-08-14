/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:33:04 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 21:35:17 by sel-mir          ###   ########.fr       */
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

int	check_if_valid(char *arg, t_data **data)
{
	static	int	i;
	long	value;

	if (iss_digit(arg))
		return (write(2, "Error: not a vaild Number !\n", 44), 1);
	value = hybrid_atoi(arg);
	if (value <= 0)
		return (1);
	if ((i == 1 || i == 2 || i == 3) && value < 60)
		return (write(2, "Error: Input a value >= 60 !", 29), 1);
	if (i == 0 && value > 200)
		return (write(2, "Error: Input a value <= 200", 28),  1);
	load_it(*data, i, value);
	i++;
	return (0);
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

t_philo	*create_philosophers(t_data *info, int total)
{
	t_philo	*new_philo;
	t_philo *philo_list;
	int		id;
	int		yet;

	(1) && (philo_list = NULL), (id = 1, yet = 0);
	while (id <= total)
	{
		new_philo = ft_lst_new(id);
		if (!new_philo)
			return (clean_all_mutex(philo_list, yet), NULL);
		new_philo->info = info;
		new_philo->last_meal = current_time();
		if (!single_mutex_init(new_philo))
			return (clean_all_mutex(philo_list, yet), NULL);
		if (!ft_lstadd_back(&philo_list, new_philo))
		{
			pthread_mutex_destroy(&new_philo->fork);
			pthread_mutex_destroy(&new_philo->meal_mutex);
			pthread_mutex_destroy(&new_philo->save_eat);
			return (clean_all_mutex(philo_list, yet), NULL);
		}
		yet++;
		id++;
	}
	return (philo_list);
}
