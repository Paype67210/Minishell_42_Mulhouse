/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_safe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:52:56 by pdeson            #+#    #+#             */
/*   Updated: 2024/03/18 17:53:00 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_safe(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst && del)
	{
		temp = *lst;
		while (temp)
		{
			temp = (*lst)->next;
			if ((*lst)->type != 0)
				ft_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}
