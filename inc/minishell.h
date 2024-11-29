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

typedef struct s_minishell
{
	char	**envp;
	char	*pathvalue;
	char	**path_list;
}	t_global;

// utils
void	enroll_custom_signal(void);
char	*ft_getenv(char *envp[], const char *env);

// builtins
int		builtin_handler(char **cmds, char **env_list);
void	ft_cd(const char *path, const char *home_path);
void	ft_exit(void);

// parser
char	*get_cmd_abspath(char *cmd);
void	parser_handler(char	*line);

#endif
