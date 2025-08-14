/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:53:27 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/14 14:58:51 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

//	This Function Wipes all the structs pointers and the strcut it self !

void	wipe_all(t_gcollct *head)
{
	t_gcollct	*hold;

	while (head)
	{
		free((*head).ptr);
		hold = head;
		head = (*head).next;
		free(hold);
	}
}

//	This Function Looks for the strcut that has the same pointer passed
//	to it and returns the struct 

void	search_gcollct(t_gcollct *head, void *ptr, t_gcollct **ret)
{
	t_gcollct	*before;
	t_gcollct	*next;

	next = NULL;
	before = NULL;
	while (head)
	{
		if ((*head).ptr == ptr)
		{
			ret[0] = before;
			ret[1] = head;
			ret[2] = next;
			return ;
		}
		before = head;
		head = (*head).next;
		if (head)
			next = (*head).next;
		else if (!head)
			next = NULL;
	}
}
