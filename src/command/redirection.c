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

static void	start_heredoc(const char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (fd != -1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

static t_bool	redirect(char *file_path, char type)
{
	int	fd;

	if (type == '>')
		fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == '+')
		fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (type == '<')
		fd = open(file_path, O_RDONLY);
	else if (type == '-')
	{
		start_heredoc(file_path);
		fd = open(".here_doc.tmp", O_RDONLY);
		unlink(".here_doc.tmp");
	}
	if (fd == -1)
	{
		print_stderr("bash: ", file_path);
		return (false);
	}
	if (type == '>' || type == '+')
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

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

t_bool	redirect_io(t_redirection *redi, int stdfd[2])
{
	if (stdfd)
	{
		stdfd[0] = dup(0);
		stdfd[1] = dup(1);
	}
	while (redi)
	{
		if (!redirect(redi->file, redi->type))
			return (false);
		redi = redi->next;
	}
	return (true);
}

void	unredirect_io(int fd[2])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}
