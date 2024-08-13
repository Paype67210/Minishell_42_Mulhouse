/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:39:58 by philippe          #+#    #+#             */
/*   Updated: 2024/06/19 15:51:35 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_lstswap(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	ft_buble_sort(t_list *head)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*ptr2;

	swapped = 1;
	ptr2 = NULL;
	if (head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != ptr2)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				ft_lstswap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	}
	return ;
}

char	*ft_value_name(char *str)
{
	char	*buffer;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_int_strchr(str, '=');
	buffer = ft_strncpy(str, (len + 1));
	return (buffer);
}

char	*ft_value(char *str)
{
	char	*buffer;

	if (!str)
		return (NULL);
	buffer = ft_strdup((ft_strchr(str, '=') + 1));
	return (buffer);
}

void	ft_print_export(t_data *data, t_list *envp)
{
	char	*buffer;
	t_list	*buff;

	buff = ft_lstfirst(envp);
	ft_buble_sort(buff);
	while (buff)
	{
		if (ft_strchr((char *)buff->content, '=') != NULL)
		{
			buffer = ft_strjoin("declare -x ", \
				ft_value_name((char *)buff->content));
			buffer = ft_strjoin(buffer, "\"");
			buffer = ft_strjoin(buffer, ft_value((char *)buff->content));
			buffer = ft_strjoin(buffer, "\"\n");
		}
		else
		{
			buffer = ft_strjoin("declare -x ", \
				ft_strdup((char *)buff->content));
			buffer = ft_strjoin(buffer, "\n");
		}
		data->result = ft_strjoin(data->result, buffer);
		buff = buff->next;
	}
}
