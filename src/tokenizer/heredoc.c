/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:49:18 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 21:49:51 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	start_heredoc(const char *delimiter, const char *tmpfile)
{
	int		fd;
	char	*line;

	fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (fd != -1)
	{
		sig_all_ign();
		line = readline("> ");
		if ((!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	handle_heredoc(t_list **tokenlst, char **line, t_word *word, t_envval *env_val)
{
	char	*tmpfile;	
	t_token	*token;

	append_token_inlist(tokenlst, word, SYMBOL, env_val);
	(*line)++;
	if (**line == ' ')
		(*line)++;
	while (**line != ' ' && **line)
	{
		append_ch_inword(word, **line);
		(*line)++;
	}
	tmpfile = ft_strjoin(".heredoc_", word->content);
	start_heredoc(word->content, tmpfile);
	free(word->content);
	init_word(word);
	token = malloc(sizeof(t_token) * 1);
	token->content = tmpfile;
	token->type = WORD;
	ft_lstadd_back(tokenlst, ft_lstnew(token));
	(*line)--;
}
