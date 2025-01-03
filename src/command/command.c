/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:00 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 19:12:04 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "../tokenizer/tokenizer.h"

static t_bool	token_tocmd_handler(t_list **cmdunit_list, t_command *command, \
									t_token *token, t_list **arg_list)
{
	static char	type;

	if (!(*cmdunit_list))
		type = 0;
	if (token->type == SYMBOL)
	{
		if (type)
			return (true);
		if (*(token->content) == '|')
		{
			append_cmd_inlist(cmdunit_list, command, CMD, arg_list);
			append_cmd_inlist(cmdunit_list, NULL, PIPE, NULL);
			command = ft_calloc(sizeof(t_command), 1);
		}
		else
			type = '>';
	}
	if (token->type == WORD)
	{
		if (type == '>')
			connect_redirection(command, token->content, type);
		else
			ft_lstadd_back(arg_list, ft_lstnew(ft_strdup(token->content)));
		type = 0;
	}
	return (false);
}

t_list *split_command(t_list *token_list)
{
	t_list		*cmdunit_list;
	t_command	*command;
	t_list		*arg_list;

	cmdunit_list = NULL;
	command = ft_calloc(sizeof(t_command), 1);
	arg_list = NULL;
	while (token_list)
	{
		if (token_tocmd_handler(&cmdunit_list, command, \
			(t_token *)token_list->content, &arg_list))
		{
			ft_lstclear(&cmdunit_list, free_cmd_unit);
			free_command(command);
			command = NULL;
			break ;
		}
		token_list = token_list->next;
	}
	append_cmd_inlist(&cmdunit_list, command, CMD, &arg_list);
	return (cmdunit_list);
}
