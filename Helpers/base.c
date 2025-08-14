/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:08:02 by sel-mir           #+#    #+#             */
/*   Updated: 2025/08/14 12:37:31 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	error(char *err)
{
	printf("\033[1;31m%s\033[0m\n", err);
}

void    ft_exit(char *why)
{
    ft_free(NULL, FREE_ALL);
    if (why)
    {
        error(why);
        exit(1);
    }
    exit(0);
}

void    *ft_malloc(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
        ft_exit("Failed to Allocate");
    ft_free(ptr, 0);
    return (ptr);
}

//	This Function handles the freeing and the Addresses Savery Avoiding Leaks !

void    ft_free(void *ptr, int flag)
{
	static	t_gcollct	*last;
	static	t_gcollct	*head;
	t_gcollct	**hold;

	hold = NULL;
	if (!head && ptr)
	{
		last = malloc(sizeof(t_gcollct));
		(*last).ptr = ptr;
		(*last).next = NULL;
		head = last;
		return;
	}

	if (!ptr && flag == FREE_ALL)
	{
		wipe_all(head);
		last = NULL;
		return ;
	}

	if (flag == FREE_ONE && head)
	{
		hold = malloc(sizeof(t_gcollct *) * 3);
		hold[1] = NULL;
		search_gcollct(head, ptr, hold);
		if (hold[1])
		{
			free((*hold[1]).ptr);
			free(hold[1]);
			if (hold[0])
				(*hold[0]).next = hold[2];
			else
				head = hold[2];
		}
		free(hold);
		return ;
	}

	else
	{
		(*last).next = malloc(sizeof(t_gcollct));
		last = (*last).next;
		(*last).ptr = ptr;
		(*last).next = NULL;
	}

}

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

void	search_gcollct(t_gcollct *head, void	*ptr, t_gcollct **ret)
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

// void	f()
// {
// 	system("leaks a.out");
// }

// int	main()
// {
// 	char *ptr;
// 	char *str;

// 	ptr = NULL;
// 	ptr = ft_malloc(sizeof(char));
// 	str = ft_malloc(sizeof(char));

// 	atexit(f);

// 	*ptr = 'A';
// 	*str = 'B';
// 	write (1, ptr, 1);
// 	write (1, " ", 1);
// 	write (1, str, 1);

// 	ft_exit("");
// }