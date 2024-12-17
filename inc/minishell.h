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

typedef enum e_token_type
{
	WORD,
	REDI,
	HERE,
	PIPE,
}	t_token_type;

typedef struct s_env
{
	struct s_list *var;
	struct s_list *env;
	int	flag_env;
	int	flag_export;
	struct s_env	*next;
}	t_env;

typedef	struct s_word
{
	char	*content;
	size_t	idx;
	size_t	max_len;
}	t_word;

typedef	struct s_token
{
	char			*content;
	t_token_type	type;
}	t_token;

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

// builtins
int		builtin_handler(char **cmds);
void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);
void	ft_env(char **cmd);
int     ft_export(char **cmds);

// parser
void	parser_handler(char	*line);
char	*get_cmd_abspath(char *cmd);
void	quote_parser(char **line, t_word *word);
void	dollar_parser(t_word *word, char *pre, size_t *i);

// token
t_list	*tokenizer(char *line);
void	append_token_inlist(t_list **token_list, t_word *word, t_token_type type);
t_token_type	get_tokentype(char ch);
char	**tokenlst_to_array(t_list *list);

// word utils
void	init_word(t_word *word);
void	append_ch_inword(t_word *word, char ch);
void	append_str_inword(t_word *word, char *str);
void	convert_wordcotent(t_word *word);

t_list	*env_list(char **envp);
t_list *arry_list(char **head);
t_env	*init_env(char **cmds);
void    set_env(char **cmds);
void    node_back(t_list **head, t_list *new);
void    value_export(char **cmds);

#endif
