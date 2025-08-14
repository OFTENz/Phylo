/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:30:49 by akella            #+#    #+#             */
/*   Updated: 2025/08/14 14:08:22 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*info;
	int		size;

	if (arg_validation(ac, av))
		return (FAILURE);
	size = hybrid_atoi(av[1]);
	philos = NULL;
	info = set_info(ac, av);
	if (!info)
		return (FAILURE);
	philos = create_philosophers(philos, info, size);
	if (!philos)
		return (cleanup_info(info), FAILURE);
	if (initialize_philo(philos, size))
		return (destroy_all(philos, size), FAILURE);
	return (destroy_all(philos, size), SUCCESS);
}

int	iss_digit(const char *str)
{
	int	i;

	if (!str)
		return (FAILURE);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (FAILURE);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (FAILURE);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (FAILURE);
	return (SUCCESS);
}
