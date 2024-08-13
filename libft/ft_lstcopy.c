/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:54:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/05/30 11:59:56 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcopy(t_list *lst)
{
	t_list	*new_list;
	t_list	*temp;

	new_list = NULL;
	while (lst)
	{
		temp = ft_lstnew(lst->content, 0, 0);
		if (!temp)
			return (NULL);
		ft_lstadd_back(&new_list, temp);
		lst = lst->next;
	}
	return (new_list);
}
