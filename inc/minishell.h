/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:47 by dukim             #+#    #+#             */
/*   Updated: 2024/11/22 21:09:48 by dukim            ###   ########.fr       */
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

typedef	struct s_word
{
	char	*content;
	size_t	idx;
	size_t	max_len;
}	t_word;

typedef struct s_minishell
{
	char	**envp;
	char	*pathvalue;
	char	**path_list;
}	t_global;

// utils
void	enroll_custom_signal(void);
char	*ft_getenv(const char *env);
void	replace_envvalue(const char *env, char	*replace);

// ft_utils
char	**ft_lstto_array(t_list *list);
t_bool	is_quote_ch(char ch);
t_bool	is_specital_ch(char ch);

// builtins
int		builtin_handler(char **cmds, char **env_list);
void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);
void	ft_env(void);

// parser
void	parser_handler(char	*line);
char	*get_cmd_abspath(char *cmd);
void	quote_parser(char **line, t_word *word);
void	dollar_parser(t_word *word, char *pre, size_t *i);

// token
t_list	*tokenizer(char *line);
void	convert_wordcotent(t_word *word);

void	init_word(t_word *word);
void	append_ch_inword(t_word *word, char ch);
void	append_str_inword(t_word *word, char *str);
void	append_token_inlist(t_list **token_list, t_word *word);

#endif
