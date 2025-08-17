/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:27 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/17 17:15:13 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*head;
	t_data	*data;

	head = NULL;
	if (arg_validation(ac, av, &data))
		return (ft_free(NULL, FREE_ALL), 1);
	if (!general_mutexe_init(data))
		return (ft_free(NULL, FREE_ALL), 1);
	if (!bag_prepa(data, &head))
		return (ft_free(NULL, FREE_ALL), 1);
	if (philo_management(head))
		return (clean_all_mutex(head,
				(*data).philos_number), ft_free(NULL, FREE_ALL), 1);
	return (clean_all_mutex(head, (*data).philos_number),
		ft_free(NULL, FREE_ALL), 0);
}

int	iss_digit(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
		return (1);
	return (0);
}

void	load_it(t_data *data, int i, int value)
{
	if (i == 0)
		(*data).philos_number = value;
	else if (i == 1)
		(*data).die_time = value;
	else if (i == 2)
		(*data).eat_time = value;
	else if (i == 3)
		(*data).sleep_time = value;
	else if (i == 4)
	{
		(*data).meal_number = value;
		(*data).fifth_arg = 1;
	}
}
