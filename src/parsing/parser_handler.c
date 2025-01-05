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
	t_list	*tokenlst;
	t_list	*cmdlst;

	if (!line || line[0] == '\0')
		return ;
	tokenlst = tokenize(line, env_val->lst);
	if (!tokenlst)
		return ;
    cmdlst = NULL;
	token_tocmdunit(tokenlst, &cmdlst);
	ft_lstclear(&tokenlst, free_token);
	if (!cmdlst)
		return ;
	execute_commands(cmdlst, env_val);
	ft_lstclear(&cmdlst, free_command);
	add_history(line);
}
