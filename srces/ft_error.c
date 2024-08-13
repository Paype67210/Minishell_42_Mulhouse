/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:45:26 by pdeson            #+#    #+#             */
/*   Updated: 2024/05/24 12:33:19 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_error(void)
{
	char	*buffer;

	buffer = ft_strjoin(strerror(errno), "\n");
	ft_putstr_fd(buffer, 2);
	ft_run_malloc(2, buffer);
}

void	ft_perror(char *str)
{
	char	*buffer;

	buffer = ft_strjoin("bash: ", str);
	perror(buffer);
	ft_run_malloc(2, buffer);
}

int	ft_code(int code)
{
	if (WIFSIGNALED(code))
	{
		code += 128;
		if (code == 131)
			printf("Quit\n");
		else if (code == 130)
			printf("\n");
	}
	g_signal = 0;
	return (code);
}
