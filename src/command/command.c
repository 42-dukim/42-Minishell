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

static t_bool	is_redirection_type(char type)
{
	if (type == '>' || type == '<' || type == '+' || type == '-')
		return (true);
	return (false);
}

static int	handle_token_tocmd(t_list **cmdunit_list, t_command **command, \
									t_token *token, t_list **arg_list)
{
	static char	type;

	if (!(*cmdunit_list) && !(*arg_list))
		type = 0;
	if (token->type == SYMBOL)
	{
		if (type)
			return (-1);
		type = *(token->content);
		if (type == '|')
		{
			append_cmd_inlist(cmdunit_list, *command, CMD, arg_list);
			append_cmd_inlist(cmdunit_list, NULL, PIPE, NULL);
			*command = ft_calloc(sizeof(t_command), 1);
		}
		return (0);
	}
	if (is_redirection_type(type))
		connect_redirection(*command, token->content, type);
	else
		ft_lstadd_back(arg_list, ft_lstnew(ft_strdup(token->content)));
	type = 0;
	return (1);
}

t_list *split_command(t_list *token_list)
{
	t_list		*cmdunit_list;
	t_command	*command;
	t_list		*arg_list;
	int			res;

	cmdunit_list = NULL;
	command = ft_calloc(sizeof(t_command), 1);
	arg_list = NULL;
	while (token_list)
	{
		res = handle_token_tocmd(&cmdunit_list, &command, \
				(t_token *)token_list->content, &arg_list);
		if (res == -1)
			break ;
		token_list = token_list->next;
	}
	if (res == 0 || res == -1)
	{
		ft_lstclear(&cmdunit_list, free_cmd_unit);
		ft_lstclear(&arg_list, free);
		free_command(command);
	}
	else
		append_cmd_inlist(&cmdunit_list, command, CMD, &arg_list);
	return (cmdunit_list);
}
