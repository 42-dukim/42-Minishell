/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:32:05 by dukim             #+#    #+#             */
/*   Updated: 2024/12/22 19:45:03 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser_handler(char *line, t_envval *env_val)
{
	t_list	*token_list;
	t_list	*cmd_list;

	if (!line || line[0] == '\0')
		return ;
	token_list = tokenizer(line, env_val->lst);
	if (!token_list)
		return ;
	cmd_list = split_command(token_list);
	ft_lstclear(&token_list, free_token);
	// print_command_list(cmd_list);
	execute_commands(cmd_list, env_val);
	ft_lstclear(&cmd_list, free_cmd_unit);
	add_history(line);
}
