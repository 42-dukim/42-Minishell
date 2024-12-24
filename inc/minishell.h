/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:47 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 21:16:20 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>

# include "../libft/libft.h"

typedef enum e_bool
{
	false = 0,
	true
}		t_bool;

typedef struct s_env
{
	struct s_list *var;
	struct s_list *env;
	int	flag_env;
	int	flag_export;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char	**envp;
	char	*pathvalue;
	char	**path_list;
	// struct s_list	*env;
	// struct s_list	*export;
	struct s_env	*link_envp;//envp로 받아온걸 리스트로 넣어둠
}	t_global;

// utils
void	enroll_custom_signal(void);
char	*ft_getenv(const char *env);
void	replace_envvalue(const char *env, char	*replace);

// ft_utils
t_bool	is_quote_ch(char ch);
t_bool	is_specital_ch(char ch);
char	**ft_lst_toarray(t_list *lst);

// builtins
int		builtin_handler(char **cmds);
void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);
void	ft_env(char **cmd);
int		ft_export(char **cmds);

// parser
void	parser_handler(char	*line);

t_list	*env_list(char **envp);
t_list	*arry_list(char **head);
t_env	*init_env(char **cmds);
void	set_env(char **cmds);
void	node_back(t_list **head, t_list *new);
void	value_export(char **cmds);

// exports module
t_list	*tokenizer(char *line);
void	free_token(void *ptr);
t_list	*split_command(t_list *token_list);
void	execute_commands(t_list *cmd_list);
void	free_cmd_unit(void *ptr);
// void	print_command_list(t_list *list);

#endif
