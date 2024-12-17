/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:47 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 21:04:03 by junkwak          ###   ########.fr       */
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


//--이거자체가 연결리스트?겸하는건가?

// typedef struct s_node//환경변수에 대한 연결리스트
// {
// 	struct s_node	*prev;
// 	struct s_node	*next;
// 	char		*value;
// }	t_node;

// typedef struct s_list_value	//env,export 에 대한 구조체2
// {
// 	struct s_node	*head;
// 	struct s_node	*tail;
// 	int		size;
// }	t_list_value;

// typedef struct s_pipe
// {
// 	int	fd[2];
// 	int	p_count;
// 	int	pid;
// 	// char	**path;
// 	// char	*order1;
// 	// char	*order2;
// }	t_pipe;


// utils
void	enroll_custom_signal(void);
char	*ft_getenv(char *envp[], const char *env);
void	replace_envvalue(const char *env, char	*replace);
int	ft_strcmp(const char *s1, const char *s2);

// builtins
int		builtin_handler(char **cmds);
void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);
void	ft_env(char **cmd);
int     ft_export(char **cmds);

// parser
char	*get_cmd_abspath(char *cmd);
void	parser_handler(char	*line);



t_list	*env_list(char **envp);
t_list *arry_list(char **head);
t_env	*init_env(char **cmds);
void    set_env(char **cmds);
void    node_back(t_list **head, t_list *new);
void    value_export(char **cmds);

//pipe
// void    pipe_inst(char *line);
// int     ft_pipe(char *split, t_pipe *pipe, int i);
// void    ft_fork(char *line, t_pipe *pipe, int **result);
#endif
