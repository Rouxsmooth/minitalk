/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:01:46 by mzaian            #+#    #+#             */
/*   Updated: 2024/12/13 17:19:20 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tempnext;

	while (*lst)
	{
		tempnext = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tempnext;
	}
	*lst = NULL;
	return ;
}
