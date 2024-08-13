/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:28:44 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/17 13:54:37 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_insert_buffer(t_list *head, t_list *buffer)
{
	if (!head->next)
	{
		head->next = buffer;
		buffer->prev = head;
	}
	else
	{
		head->next->prev = ft_lstlast(buffer);
		ft_lstlast(buffer)->next = head->next;
		head->next = buffer;
		buffer->prev = head;
	}
	return ;
}

void	ft_replace_wc(t_data *data, t_list *prompt, char **files, int i)
{
	t_list	*head;
	t_list	*buffer;
	char	*tmp;

	head = prompt->prev;
	tmp = ft_strdup(prompt->content);
	buffer = ft_lstretrieve(&data->prompt, prompt);
	while (files[i] && files[i][0])
	{
		if (ft_wildcmp(files[i], tmp))
		{
			if (buffer->type == WILDCARD)
			{
				ft_run_malloc(3, buffer->content, ft_strlen(files[i]) + 1);
				buffer->content = ft_strdup(files[i]);
				buffer->type = TEXTE;
			}
			else
				ft_lstadd_back(&buffer, ft_lstnew(files[i], TEXTE, VIDE));
		}
		i++;
	}
	ft_insert_buffer(head, buffer);
	ft_run_malloc(2, tmp);
	return ;
}

bool	ft_wildcmp(char *str, char *pattern)
{
	while (*str && *pattern)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (*pattern == '\0')
				return (true);
			while (*str)
			{
				if (ft_wildcmp(str, pattern))
					return (true);
				str++;
			}
			return (false);
		}
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (false);
	}
	return (*str == '\0' && *pattern == '\0');
}
