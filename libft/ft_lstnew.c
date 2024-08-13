/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:43:24 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/16 14:13:58 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int type, size_t size)
{
	t_list	*node;

	node = (t_list *)ft_run_malloc(1, sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->size = size;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
