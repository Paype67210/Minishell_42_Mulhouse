/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 15:36:07 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*str;

	ft_initialisation(&data, argc, argv, envp);
	while (1)
	{
		ft_signal();
		struct_init(&data);
		str = readline(data.line);
		if (str == NULL)
			ft_ctrl_d_handler(&data);
		data.exit_code = check_args(&data, str);
		if (data.history)
			add_history(data.history);
		data.prompt = ft_lstfirst(data.prompt);
		errno = 0;
		ft_print_debug(&data);
		data.prompt = ft_lstfirst(data.prompt);
		if (data.exit_code == 0)
			execution(&data);
		data.exit_code = data.exit_code % 256;
	}
	ft_exit(&data);
	return (data.exit_code);
}
