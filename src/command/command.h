/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:26 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 19:12:27 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../../inc/minishell.h"

typedef struct s_redirection
{
    char					type;
    char					*file;
    struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char			**args;
	t_redirection	*redi;
}	t_command;

// redirection
void	connect_redirection(t_command *command, char *file, char type);
t_bool	redirect_io(t_redirection *redi, int stdfd[2]);
void	unredirect_io(int fd[2]);

// utils
char	*get_cmd_abspath(char *cmd, char **path_list);
void	append_cmd_inlist(t_list **lst, t_command *command, t_list **arg_list);

#endif
