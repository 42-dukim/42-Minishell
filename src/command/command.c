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

static void	append_cmd_inlist(t_list **lst, t_command *command, t_cmd_type type, t_list **arg_list)
{
	t_cmd_unit	*cmd_unit;

	if (type == CMD)
		command->args = ft_lst_toarray(*arg_list);
	cmd_unit = malloc(sizeof(t_cmd_unit *) * 1);
	cmd_unit->type = type;
	cmd_unit->cmd = command;
	ft_lstadd_back(lst, ft_lstnew(cmd_unit));
}

static void connet_redirection(t_command *command, char *file, char type)
{
	t_redirection	*ptr;
	t_redirection	*redi;

	redi = malloc(sizeof(t_redirection) * 1);
	redi->file = ft_strdup(file);
	redi->type = type;
	redi->next = NULL;
	if (command->redi == NULL)
		command->redi = redi;
	else
	{
		ptr = command->redi;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = redi;
	}
}

static t_bool	token_tocmd_handler(t_command *command, t_token *token, t_list **arg_list)
{
	static char	type;

	if (token->type == WORD)
	{
		if (type)
			connet_redirection(command, token->content, type);
		else
			ft_lstadd_back(arg_list, ft_lstnew(ft_strdup(token->content)));
		type = 0;
	}
	if (token->type == SYMBOL)
	{
		if (*(token->content) == '>')
			type = '>';
		if (*(token->content) == '>' && token->content[1] == '>')
			type = '+';
		if (*(token->content) == '<')
			type = '<';
		if (*(token->content) == '|')
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
	return (cmdunit_list);
}
