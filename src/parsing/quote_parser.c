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

static char	*get_quote_token(char **line)
{
	char	*quote_token;
	char	quote;
	size_t	i;

	quote_token = ft_calloc(sizeof(char), ft_strlen(*line) + 1);
	quote = 0;
	i = 0;
	while (**line)
	{
		quote_token[i++] = **line;
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
		free(quote_token);
		return (NULL);
	}
	return (quote_token);
}

char	*quote_parser(char **line, char *token)
{
	char	*quote_token;
	char	*temp;
	char	quote;

	quote = **line;
	quote_token = get_quote_token(line);
	if (!quote_token)
	{
		free(token);
		return (NULL);
	}
	temp = quote_token;
	quote_token = ft_strjoin(token, quote_token);
	free(temp);
	free(token);
	return (quote_token);
}