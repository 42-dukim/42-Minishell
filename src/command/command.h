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

typedef enum e_command_type
{
	CMD,
	PIPE,
}	t_cmd_type;

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

typedef struct s_command_unit
{
	t_cmd_type	type;
	t_command	*cmd;
}	t_cmd_unit;

// utils
char	*get_cmd_abspath(char *cmd, t_list *env_list);

#endif
