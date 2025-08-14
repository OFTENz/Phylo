/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:33:04 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 12:13:53 by sel-mir          ###   ########.fr       */
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

int	check_if_valid(char *arg)
{
	static	int	i;
	long	value;

	if (iss_digit(arg))
		return (write(2, "Error: not a vaild Number !\n", 44), FAILURE);
	value = hybrid_atoi(arg);
	if (value <= 0)
		return (FAILURE);
	if ((i == 1 || i == 2 || i == 3) && value < 60)
		return (write(2, "Error: Input a value >= 60 !", 29), FAILURE);
	if (i == 0 && value > 200)
		return (write(2, "Error: Input a value <= 200", 28),  FAILURE);
	i++;
	return (SUCCESS);
}

int	arg_validation(int argc, char **av)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (write(2, "Inavlid Arguments !\n", 34), FAILURE);
	i = 1;
	while (i < argc)
	{
		if (check_if_valid(av[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
