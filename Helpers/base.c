/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:52:45 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/14 20:35:57 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"


void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_free(NULL, FREE_ALL);
		return (NULL);
	}
	ft_free(ptr, 0);
	return (ptr);
}

//	This Function handles the freeing and the Addresses Savery Avoiding Leaks !

void	ft_free(void *ptr, int flag)
{
	static t_gcollct	*last;
	static t_gcollct	*head;
	t_gcollct			**hold;
	if (flag == FREE_ALL)
		dprintf(2, "\nRunned !\n");
	hold = NULL;
	if (!head && ptr)
	{
		last = malloc(sizeof(t_gcollct));
		(*last).ptr = ptr;
		(*last).next = NULL;
		head = last;
		return ;
	}
	if (!ptr && flag == FREE_ALL)
		return (wipe_all(head), (last = NULL), (void)0);
	if (flag == FREE_ONE && head)
	{
		free_one(hold, head, ptr);
		return (free(hold));
	}
	else
	{
		(*last).next = malloc(sizeof(t_gcollct));
		(1) && (last = (*last).next, (*last).ptr = ptr, (*last).next = NULL);
	}
}

void	free_one(t_gcollct **hold, t_gcollct *head, void *ptr)
{
	hold = malloc(sizeof(t_gcollct *) * 3);
	hold[1] = NULL;
	search_gcollct(head, ptr, hold);
	if (hold[1])
	{
		(free((*hold[1]).ptr)), (free(hold[1]));
		if (hold[0])
			(*hold[0]).next = hold[2];
		else
			head = hold[2];
	}
}