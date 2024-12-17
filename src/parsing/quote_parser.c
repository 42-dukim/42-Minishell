/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:45:38 by dukim             #+#    #+#             */
/*   Updated: 2024/12/06 19:45:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_quotetoken_content(char **line)
{
	char	*content;
	char	quote;
	size_t	i;

	content = ft_calloc(sizeof(char), ft_strlen(*line) + 1);
	quote = 0;
	i = 0;
	while (**line)
	{
		content[i++] = **line;
		if (is_quote_ch(**line))
		{
			if (quote == 0)
				quote = **line;
			else if (quote == **line)
				break ;
		}
		(*line)++;
	}
	if (**line != quote)
	{
		free(content);
		return (NULL);
	}
	return (content);
}

void	quote_parser(char **line, t_token *token)
{
	char	*content;
	char	*temp;

	content = get_quotetoken_content(line);
	if (!content)
	{
		free(token->content);
		token->content = NULL;
		token->idx = 0;
		return ;
	}
	temp = token->content;
	token->content = ft_strjoin(token->content, content);
	token->max_len = ft_strlen(token->content);
	token->idx = token->max_len;
	free(temp);
	free(content);
}