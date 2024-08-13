/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:17 by pdeson            #+#    #+#             */
/*   Updated: 2024/05/26 16:14:03 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_get_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				file_count;
	char			*cwd;

	cwd = getcwd(NULL, 0);
	dir = opendir(cwd);
	if (!dir)
		return (0);
	file_count = 0;
	entry = readdir(dir);
	if (entry)
		file_count = 1;
	while (entry)
	{
		file_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	ft_run_malloc(2, cwd);
	return (file_count);
}

void	ft_get_files_name(char **files, char *cwd, int *i)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		file_stat;
	char			*entry_path;

	dir = opendir(cwd);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		entry_path = ft_strjoin(cwd, "/");
		entry_path = ft_strjoin(entry_path, (char *)entry->d_name);
		if (stat(entry_path, &file_stat) == 0)
		{
			if ((S_ISREG(file_stat.st_mode) || S_ISDIR(file_stat.st_mode)) \
				&& (entry->d_name[0] != '.'))
				files[i[1]++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return ;
}

char	**ft_main_wc(void)
{
	char			**files;
	char			*cwd;
	int				*i;

	i = ft_run_malloc(1, sizeof(int) * 2);
	if (!i)
		exit (EXIT_FAILURE);
	i[0] = ft_get_files();
	i[1] = 0;
	cwd = getcwd(NULL, 0);
	files = ft_run_malloc(1, sizeof(char *) * (i[0] + 1));
	if (!files)
		return (NULL);
	ft_get_files_name(files, cwd, i);
	free(cwd);
	return (files);
}
