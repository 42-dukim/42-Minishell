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
	char	*temp;
	char	quote;
	size_t	j;

	quote_token = ft_calloc(sizeof(char), ft_strlen(*line) + 1);
	quote = '\0';
	j = 0;
	while (**line)
	{
		quote_token[j] = **line;
		j++;
		if (**line == '\'' || **line == '"')
		{
			if (!quote)
				quote = **line;
			else if (quote == **line)
				break ;
		}
		(*line)++;
	}
	if (**line != quote)
	{
		free(quote_token);
		if (**line == '\0')
			(*line)--;
		return (ft_strdup(""));
	}
	temp = quote_token;
	quote_token = ft_strdup(quote_token);
	free(temp);
	return (quote_token);
}

char	*quote_parser(char **line, char *token)
{
	char	*quote_token;
	char	*temp;
	char	quote;

	quote = **line;
	quote_token = get_quote_token(line);
	temp = quote_token;
	quote_token = ft_substr(quote_token, 1, ft_strlen(quote_token) - 2);
	free(temp);
	if (quote == '"')
		quote_token = dollar_parser(quote_token);
	temp = quote_token;
	quote_token = ft_strjoin(token, quote_token);
	free(temp);
	free(token);
	return (quote_token);
}