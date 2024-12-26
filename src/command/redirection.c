/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:27:42 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 13:27:43 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	connect_redirection(t_command *command, char *file, char type)
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

void	redirect_io(t_redirection *redi)
{
	int	fd;

	while (redi)
	{
		if (redi->type == '>')
		{
			fd = open(redi->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		if (redi->type == '<')
		{
			fd = open(redi->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		// TODO: >>, <<
		close(fd);
		redi = redi->next;
	}
}

void	unredirect_io()
{
	
}