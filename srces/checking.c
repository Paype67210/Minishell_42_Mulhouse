/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 16:29:01 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_args(t_data *data, char *str)
{
	if (access(".ctrlc", F_OK) == 0)
	{
		data->old_exit_code = 130;
		unlink(".ctrlc");
	}
	if (!str || ft_strlen(str) == 0)
		return (0);
	data->count_check = 0;
	data->history = str;
	getcwd(data->path, sizeof(data->path));
	str = add_space(ft_strjoin(str, "\0"));
	data->strcpy = ft_split_check(str, ' ');
	if (!data->strcpy || data->strcpy[0] == NULL)
		return (130);
	while (data->strcpy[data->count_check] != NULL)
	{
		ft_lstadd_back(&data->prompt, \
			ft_lstnew(data->strcpy[data->count_check], 0, 0));
		data->prompt = data->prompt->next;
		data->count_check++;
	}
	check_args2(data);
	data->exit_code = second_check_args(data);
	chdir(data->path);
	return (data->exit_code);
}

void	check_args2(t_data *data)
{
	data->prompt = ft_lstfirst(data->prompt);
	while (1)
	{
		data->prompt->content = if_dollar(data, data->prompt->content);
		data->prompt->content = if_quote(data, data->prompt->content, 0);
		data->prompt->type = check_command(data, data->prompt->content);
		data->prompt->execve_path = data->execve_path;
		data->execve_path = NULL;
		if (data->prompt->next == NULL)
			break ;
		data->prompt = data->prompt->next;
	}
	return ;
}

int	check_command(t_data *data, char *str)
{
	if ((ft_strrchr(str, '(') != NULL) && (data->prompt->type != TEXTE))
		return (ft_prt(data));
	else if ((ft_strrchr(str, ')') != NULL) && (data->prompt->type != TEXTE))
		return (CPRT);
	else if (ft_strstr(str, "echo") >= 0 && ft_strlen(str) == 4)
		return (ECHO1);
	else if (ft_strstr(str, "cd") >= 0 && ft_strlen(str) == 2)
		return (CD);
	else if (ft_strstr(str, "pwd") >= 0 && ft_strlen(str) == 3)
		return (PWD);
	else if (ft_strstr(str, "export") >= 0 && ft_strlen(str) == 6)
		return (EXPORT);
	else if (ft_strstr(str, "unset") >= 0 && ft_strlen(str) == 5)
		return (UNSET);
	else if (ft_strstr(str, "env") >= 0 && ft_strlen(str) == 3)
		return (ENV);
	else if (ft_strstr(str, "exit") >= 0 && ft_strlen(str) == 4)
		return (EXIT);
	else if ((chdir(str) == -1) && \
		(access(str, X_OK) >= 0) && (access(str, F_OK) >= 0))
		return (EXEC);
	else if (ft_execve(data, str) == 0)
		return (CMD);
	else
		return (check_sign(data, str));
}

int	check_sign(t_data *data, char *str)
{
	if (str[0] == '-')
		return (OPTION);
	if (data->prompt->type == TEXTE)
		return (TEXTE);
	if (ft_strstr(str, ">") >= 0 && ft_strlen(str) == 1)
		return (DIROUT);
	else if (ft_strstr(str, ">>") >= 0 && ft_strlen(str) == 2)
		return (DIROUT2);
	else if (ft_strstr(str, "<") >= 0 && ft_strlen(str) == 1)
		return (DIRIN2);
	else if (ft_strstr(str, "<<") >= 0 && ft_strlen(str) == 2)
		return (HEREDOC);
	else if (ft_strstr(str, "|") >= 0 && ft_strlen(str) == 1)
		return (PIPE);
	else if (ft_strstr(str, "||") >= 0 && ft_strlen(str) == 2)
		return (OU);
	else if (ft_strstr(str, "&&") >= 0 && ft_strlen(str) == 2)
		return (ET);
	else if ((ft_strchr(str, '*') != NULL))
		return (WILDCARD);
	return (TEXTE);
}

int	ft_execve(t_data *data, char *str)
{
	char	**path;
	int		i;

	if (ft_strlen(str) == 0)
		return (1);
	data->envp_bis = ft_lstfirst(data->envp_bis);
	while (ft_strstr(ft_strbtwcpy2(data->envp_bis->content, -1, '='), \
		"PATH") == -1 && data->envp_bis->next != NULL)
		data->envp_bis = data->envp_bis->next;
	if (data->envp_bis->next == NULL)
		return (1);
	path = ft_split((ft_strnlcpy(data->envp_bis->content, 5)), ':');
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], str);
		if (access(path[i], X_OK) == 0)
			data->execve_path = path[i];
		if (access(path[i], X_OK) == 0)
			return (0);
		else
			ft_run_malloc(2, path[i]);
	}
	return (ft_run_malloc(2, path), 1);
}
