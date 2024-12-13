/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:47 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 14:37:01 by junkwak          ###   ########.fr       */
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

typedef struct s_minishell
{
	char	**envp;
	char	*pathvalue;
	char	**path_list;
}	t_global;

typedef struct s_pipe
{
	int	fd[2];
	int	p_count;
	int	pid;
	// char	**path;
	// char	*order1;
	// char	*order2;
}	t_pipe;


// utils
void	enroll_custom_signal(void);
char	*ft_getenv(char *envp[], const char *env);
void	replace_envvalue(const char *env, char	*replace);

// builtins
int		builtin_handler(char **cmds, char **env_list);
void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);
void	ft_env(char **cmds);

// parser
char	*get_cmd_abspath(char *cmd);
void	parser_handler(char	*line);


//pipe
void    pipe_inst(char *line);
int     ft_pipe(char *split, t_pipe *pipe, int i);
void    ft_fork(char *line, t_pipe *pipe, int **result);
#endif
