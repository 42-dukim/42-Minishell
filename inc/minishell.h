/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:47 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 18:12:06 by junkwak          ###   ########.fr       */
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
	char *key;
	char *value;
}	t_env;

typedef	struct s_envvalue
{
	t_list	*lst;
	char	**envp;
	t_bool	is_changed;
	char	**paths;
}	t_envval;

// utils
void	enroll_custom_signal(void);

// env utils
char	*ft_getenv(const char *env, t_list *env_list);
void	replace_envvalue(const char *env, char *replace, t_list *env_list);
t_list	*init_env_list(char **envp);
void	free_env(void *ptr);

// ft_utils
t_bool	is_quote_ch(char ch);
char	**ft_lst_toarray(t_list *lst);
char	**ft_strdivide(char *str, int c);

// error utils
void	print_stderr(const char *str1, const char *str2);

// builtins
t_bool	is_builtin_cmd(char *cmd);
void	builtin_handler(void *ptr, t_envval *env_val);

// parser
void	parser_handler(char *line, t_envval *env_val);

// exports module
t_list	*tokenize(char *line, t_list *env_list);
void	free_token(void *ptr);
t_list	*split_command(t_list *token_list);
void	execute_commands(t_list *cmd_list, t_envval *env_val);
void	free_cmd_unit(void *ptr);

#endif
