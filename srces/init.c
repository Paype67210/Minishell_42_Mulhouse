/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 12:04:00 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_shlvl_plus(t_data *data)
{
	t_list	*buffer;
	t_list	*token;
	char	*tmp;
	int		i;

	buffer = data->envp_bis;
	while (buffer && buffer->content)
	{
		tmp = (char *)buffer->content;
		if (!strncmp(tmp, "SHLVL=", 6))
			break ;
		buffer = buffer->next;
	}
	if (!buffer || !buffer->content)
	{
		token = ft_lstnew("SHLVL=1", VIDE, VIDE);
		ft_lstadd_back(&data->envp_bis, token);
	}
	else
	{
		i = ft_atoi((ft_strchr(buffer->content, '=') + 1)) + 1;
		tmp = ft_strjoin("SHLVL=", ft_itoa(i));
		token = ft_lstnew(tmp, VIDE, VIDE);
		ft_change_value(data, token, (char *)token->content);
	}
}

int	ft_initialisation(t_data *data, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	errno = 0;
	g_signal = 0;
	data->exit_code = 0;
	ft_open_stderr(&data->fd_log);
	if (dup2(data->fd_log, STDERR_FILENO) == -1 || close(data->fd_log) == -1)
		return (ft_msg("Error: ", "dup2 STDERR failed\n", NULL, 1));
	data->envp_bis = NULL;
	if (ft_init_env(data, env) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_init_env(t_data *data, char **env)
{
	t_list	*node;
	char	*str;
	int		i;

	i = -1;
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		if (!str)
		{
			ft_lstclear(&data->envp_bis, &free);
			ft_error();
			return (-1);
		}
		node = ft_lstnew(str, VIDE, VIDE);
		if (!node)
		{
			ft_run_malloc(2, str);
			ft_lstclear(&node, &free);
			return (ft_error(), -1);
		}
		ft_lstadd_back(&data->envp_bis, node);
	}
	ft_shlvl_plus(data);
	return (0);
}

char	*init_line(t_data *data, char *mem)
{
	char	*line;

	data->envp_bis = ft_lstfirst(data->envp_bis);
	mem = getcwd(NULL, 0);
	if (!mem)
	{
		chdir("..");
		mem = getcwd(NULL, 0);
	}
	line = ft_strdup(mem);
	while (ft_strchr(line, '/') != NULL)
		line = ft_strbtwcpy(line, '/', '\0');
	line = ft_strjoin("@:~/", line);
	while (1)
	{
		if (ft_strstr(ft_strbtwcpy2(data->envp_bis->content, -1, '='), \
			"USER") >= 0)
			line = ft_strjoin(ft_strbtwcpy2(data->envp_bis->content, \
				4, '\0'), line);
		if (data->envp_bis->next == NULL)
			break ;
		data->envp_bis = data->envp_bis->next;
	}
	data->envp_bis = ft_lstfirst(data->envp_bis);
	return (line = ft_strjoin(line, "$ "), free(mem), line);
}

void	struct_init(t_data *data)
{
	char	*mem;

	mem = ft_run_malloc(1, sizeof(char *));
	signal(SIGQUIT, SIG_IGN);
	data->paths = NULL;
	data->execve_path = NULL;
	if (!data->exit_code)
		data->old_exit_code = 0;
	else
		data->old_exit_code = data->exit_code;
	data->exit_code = 0;
	data->prompt = ft_lstnew(NULL, VIDE, VIDE);
	data->result = NULL;
	data->std_in = NULL;
	data->std_out = ft_lstnew(NULL, VIDE, VIDE);
	data->std_out->content = NULL;
	data->std_out->type = VIDE;
	data->history = NULL;
	data->pipes = NULL;
	data->nb_pipes = VIDE;
	data->fd[0] = VIDE;
	data->fd[1] = VIDE;
	data->line = init_line(data, mem);
	return ;
}
