/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainlist_to_dblpoint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:46:06 by pdeson            #+#    #+#             */
/*   Updated: 2024/05/06 10:38:56 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**chainlist_to_dblpoint(t_list *envp)
{
	char	**args;
	int		i;

	if (!envp)
		return (NULL);
	args = ft_run_malloc(1, (ft_lstsize(envp) + 1) * sizeof(char *));
	i = -1;
	while (1)
	{
		args[++i] = envp->content;
		if (envp->next == NULL)
			break ;
		envp = envp->next;
	}
	args[i + 1] = NULL;
	return (args);
}
