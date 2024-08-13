/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:58:57 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 13:19:39 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <linux/fb.h>
# include <time.h>

/* Type in Data for metacharacters */

enum e_metas {
	VIDE,
	ECHO1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	EXEC,
	CMD,
	DIROUT = 11,
	DIROUT2,
	DIRIN2,
	HEREDOC,
	PIPE,
	OU,
	ET,
	WILDCARD,
	DOLLARS = 21,
	DOLLARS2,
	DQUOTE,
	SQUOTE,
	FILE1,
	REPERT,
	OPTION,
	TEXTE,
	OPRT,
	CPRT
};
# define LOG_DIR "./.varlog"
# define FILE_PREFIX "debug"

/* Structure */

extern int	g_signal;

typedef struct data_s
{
	char	path[4096];
	t_list	*envp_bis;
	t_list	*prompt;
	char	*execve_path;
	int		count_check;
	char	**strcpy;
	char	**paths;
	int		fd[2];
	int		*pipes;
	pid_t	*num_pid;
	int		nb_pipes;
	char	*std_in;
	t_list	*std_out;
	char	*result;
	int		old_exit_code;
	int		exit_code;
	char	*history;
	char	*line;
	int		fd_log;
}			t_data;

typedef struct s_wild
{
	char	*str;
	char	*expr;
	int		str_len;
	int		expr_len;
}			t_wild;

/* main.c */
void			find_signal(int signum);
void			check_signal(void);
int				main(int argc, char **argv, char **envp);

/* init.c */
void			ft_shlvl_plus(t_data *data);
int				ft_initialisation(t_data *data, \
					int argc, char **argv, char **env);
void			struct_init(t_data *data);
char			*init_line(t_data *data, char *mem);
int				ft_init_env(t_data *data, char **env);

/* utils.c */
char			*dblptr_to_ptr(char **str);
char			*ft_here_doc(char *str, char chr);
int				ft_findplus(const char *src, const char *value);
void			ft_remove_if_exist(t_data *data, char *new_value);
t_list			*ft_extract_if_exist(t_data *data, char *value);

/* utils2.c */
int				count_pipe(t_list *lst);
int				ft_exec_redi_opt2(t_data *data);
void			ft_sig_handler3(int sig);
void			ft_exec_stdin(t_data *data);
void			ft_exec_stdout(t_data *data);

/* utils3.c */
int				check_std2(t_data *data, int i, int fd);
int				check_std(t_data *data);
int				close_all(t_data *data, int i);
void			two_close(t_data *data, int i);

/* utils4.c */
void			trucmuche(t_data *data);
int				start_fils(t_data *data, int i);
void			ft_blurp(t_data *data);

/* checking.c */
int				check_args(t_data *data, char *str);
void			check_args2(t_data *data);
int				check_command(t_data *data, char *str);
int				check_sign(t_data *data, char *str);
int				ft_execve(t_data *data, char *str);

/* second_checking.c */
int				second_check_args(t_data *data);
int				heredoc_end(t_data *data);
int				second_check_command(t_data *data);
int				second_check_sign(t_data *data);

/* execution.c */
int				which_command(t_data *data);
int				which_sign(t_data *data);
int				parent(t_data *data);
int				ft_execution2(t_data *data);
int				execution(t_data *data);

/* if_command1.c */
int				if_echo(t_data *data);
int				if_cd(t_data *data);
int				if_pwd(t_data *data);
int				if_export(t_data *data);
int				if_unset(t_data *data);

/* if_command2.c */
int				if_env(t_data *data);
int				if_exit(t_data *data);
int				if_exec(t_data *data);
int				if_execve(t_data *data);

/* if_sign1.c */
int				if_redi_opt(t_data *data);
int				if_dbl_redi_opt(t_data *data);
int				if_redi_ipt(t_data *data);
int				if_here_doc(t_data *data);
int				ft_exec_here_doc2(t_data *data);

/* if_sign2.c */
int				if_pipe(t_data *data);
int				if_dbl_pipe(t_data *data);
int				if_dbl_esp(t_data *data);
int				if_wild(t_data *data);

/* if_dollar.c */
char			*dollar_join(t_data *data, char *str, int i, int j);
char			*dollar_join2(t_data *data, char *str);
char			*if_dollar(t_data *data, char *str);
char			*if_dollar_buff(t_data *data, char *str, int i, int j);
int				if_dollar_i(char *str);

/* if_other1.c */
int				if_parenthese(t_data *data);
int				if_parenthese2(t_data *data);
char			*ft_strbtwcpyi(char *str, int i, int j);
char			*if_quote(t_data *data, char *str, int i);

/* if_other2.c */
int				if_env_variable(char *str);
int				ft_prt(t_data *data);
int				while_prt(char *str, int i);
int				idk(t_data *data);
char			*add_space(char	*str);

/* ft_split_check.c */
char			*if_prt(char *str, int i);
char			*count_prompt(char *str);
char			*ft_strbtwcpy2(char *str, int i, char chr2);
char			**ft_split_check(char *s, char c);

/* ft_error.c */
void			ft_error(void);
void			ft_perror(char *str);
int				ft_code(int code);

/* ft_exit.c */
void			ft_print_result(t_data *data);
void			ft_exit(t_data *data);

/* ft_exec_echo.c */
int				ft_exec_cd2(t_data *data);
int				ft_exec_echo(t_data *data);

/* ft_exec_cd.c */
int				ft_exec_cd(t_data *data);

/* ft_exec_pwd.c */
int				ft_exec_pwd(t_data *data);

/* ft_exec_unset.c */
void			ft_remove_if_exist2(t_data *data);
int				ft_exec_unset(t_data *data);

/* ft_exec_export.c */
char			*ft_newvalue(char *str);
void			ft_change_value(t_data *data, t_list *token, char *str);
int				ft_verif_name(char *str, int type);
int				ft_export_value(t_list **envp, char *str, int type);
int				ft_exec_export(t_data *data);

/* ft_exec_env.c */
int				ft_exec_env(t_data *data);

/* ft_exec_exit.c */
int				ft_exec_exit(t_data *data);

/* ft_exec_execve.c */
int				ft_execve_args2(t_data *data, char **args, int i);
char			**ft_execve_args(t_data *data);
int				fils(t_data *data, int i);
int				ft_exec_execve2(t_data *data, int i);
int				ft_exec_execve(t_data *data);

/* ft_exec_redi_ipt.c */
int				ft_exec_redi_ipt(t_data *data);

/* ft_exec_dbl_redi_ipt.c */
int				ft_exec_dbl_redi_opt(t_data *data);

/* ft_exec_here_doc.c */
int				ft_exec_here_doc(t_data *data);

/* ft_exec_pipe.c */
int				ft_exec_pipe(t_data *data);

/* ft_exec_dbl_pipe.c */
int				ft_exec_dbl_pipe(t_data *data);

/* ft_exec_dbl_esp.c */
int				ft_exec_dbl_esp(t_data *data);

/* ft_exec_prt.c */
int				ft_exec_prt2(t_data *data);
int				ft_exec_prt(t_data *data);

/* ft_exec_other.c */
int				ft_exec_other(t_data *data);

/* ft_sort_list.c */
void			ft_sort_list(t_list *list);
void			ft_swap(t_list *a, t_list *b);

/* chainlist_to_dblpoint.c */
char			**chainlist_to_dblpoint(t_list *envp);

/* chainlist_to_dblpoint.c */
char			**chainlist_to_dblpoint(t_list *envp);

/* ft_print_export.c */
void			ft_lstswap(t_list *a, t_list *b);
void			ft_buble_sort(t_list *head);
void			ft_print_export(t_data *data, t_list *envp);

/* ft_signal.c */
void			ft_sig_handler(int sig);
void			ft_signal(void);
int				ft_ctrl_d_handler(t_data *data);
void			ft_sig_handler2(int sig);
void			ft_signal2(void);

/* ft_wildcards.c */
int				ft_get_files(void);
void			ft_get_files_name(char **files, char *cwd, int *i);
char			**ft_main_wc(void);

/* ft_wildcards_utils.c */
bool			ft_wildcmp(char *str, char *pattern);
void			ft_replace_wc(t_data *data, t_list \
					*prompt, char **files, int i);

/* ft_DEBUG.c */

void			ft_print_debug(t_data *data);

#endif
