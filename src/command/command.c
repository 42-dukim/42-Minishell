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

static t_bool	token_tocmd_handler(t_command *command, t_token *token, t_list **arg_list)
{
	static char	type;

	if (token->type == WORD)
	{
		if (type)
			connect_redirection(command, token->content, type);
		else
			ft_lstadd_back(arg_list, ft_lstnew(ft_strdup(token->content)));
		type = 0;
	}
	if (token->type == SYMBOL)
	{
		type = *(token->content);
		if (type == '|')
			return (true);
	}
	return (false);
}

t_list *split_command(t_list *token_list)
{
	t_list		*cmdunit_list;
	t_list		*ptr;
	t_command	*command;
	t_list		*arg_list;

	cmdunit_list = NULL;
	ptr = token_list;
	command = malloc(sizeof(t_command) * 1);
	ft_memset(command, 0, sizeof(t_command));
	arg_list = NULL;
	while (ptr)
	{
		if (token_tocmd_handler(command, (t_token *)ptr->content, &arg_list))
		{
			append_cmd_inlist(&cmdunit_list, command, CMD, &arg_list);
			append_cmd_inlist(&cmdunit_list, NULL, PIPE, NULL);
			ft_lstclear(&arg_list, free);
			command = malloc(sizeof(t_command) * 1);
			ft_memset(command, 0, sizeof(t_command));
		}
		ptr = ptr->next;
	}
	append_cmd_inlist(&cmdunit_list, command, CMD, &arg_list);
	ft_lstclear(&arg_list, free);
	return (cmdunit_list);
}
