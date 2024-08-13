/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:17:26 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/17 16:19:48 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT && g_signal == 0)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		open(".ctrlc", O_CREAT, 0644);
	}
	if (sig == SIGQUIT && g_signal == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_signal(void)
{
	if (signal(SIGINT, &ft_sig_handler) == SIG_ERR \
		|| signal(SIGQUIT, &ft_sig_handler) == SIG_ERR)
	{
		ft_putstr_fd("Minishell", 2);
		ft_putendl_fd(": Cannot catch signal. Aborting", 2);
		exit(1);
	}
}

int	ft_ctrl_d_handler(t_data *data)
{
	ft_exit(data);
	return (0);
}

void	ft_sig_handler2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_redisplay();
		exit(130);
	}
}

void	ft_signal2(void)
{
	if (signal(SIGINT, &ft_sig_handler2) == SIG_ERR)
	{
		ft_putstr_fd("Minishell", 2);
		ft_putendl_fd(": Cannot catch signal. Aborting", 2);
		exit(1);
	}
}
