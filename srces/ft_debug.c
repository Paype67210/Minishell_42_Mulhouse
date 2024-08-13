/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: philippe <philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:22:15 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/20 15:14:22 by philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_print_debug(t_data *data)
{
	t_list	*buffer;

	buffer = ft_lstfirst(data->prompt);
	ft_fprintf(2, "-==-==-==-==-\n");
	while (buffer)
	{
		ft_fprintf(2, "[ %s -> %i] ", (char *)buffer->content, buffer->type);
		buffer = buffer->next;
	}
	ft_fprintf(2, "\n-==-==-==-==-\n");
}
