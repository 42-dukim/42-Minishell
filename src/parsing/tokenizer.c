/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:36:23 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 19:36:24 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define TOKEN_LEN 10

static void	init_token(char **token, size_t *idx, size_t *len)
{
	*idx = 0;
	*len = TOKEN_LEN;
	*token = ft_calloc(sizeof(char), *len + 1);
}

static void	extend_str(char **str, size_t *size)
{
	char	*extend;

	*size *= 2;
	extend = ft_calloc(sizeof(char), *size + 1);
	ft_strlcpy(extend, *str, *size / 2 + 1);
	free(*str);
	*str = extend;
}

static	char *convert_token(char *token)
{
	char	*new;
	char	*temp;
	char	quote;
	size_t	i;

	temp = token;
	new = ft_calloc(sizeof(char), ft_strlen(token) + 1);
	quote = 0;
	i = 0;
	while(*token)
	{
		if (is_quote_ch(*token))
		{
			if (quote == 0)
				quote = *token;
			else if (quote == *token)
				quote = 0;
			else
				new[i++] = *token;
			token++;
			continue ;
		}
		if (*token == '$' && quote != '\'')
		{
			i += dollar_parser(&token, new + i);
			continue;
		}
		new[i++] = *token++;
	}
	free(temp);
	return (new);
}

t_list	*tokenizer(char *line)
{
	t_list	*token_list;
	char	*token;
	size_t	token_len;
	size_t	i;

	token_list = NULL;
	init_token(&token, &i, &token_len);
	line--;
	while (*(++line))
	{
		if (is_quote_ch(*line))
		{
			token = quote_parser(&line, token);
			if (!token)
			{
				ft_lstclear(&token_list, free);
				return (NULL);
			}
			token_len = ft_strlen(token);
			i = token_len;
			continue ;
		}
		if (*line == ' ')
		{
			if (i == 0)
				continue ;
			ft_lstadd_back(&token_list, ft_lstnew(convert_token(token)));
			init_token(&token, &i, &token_len);
			continue ;
		}
		if (i == token_len)
			extend_str(&token, &token_len);
		token[i++] = *line;
	}
	if (i > 0)
		ft_lstadd_back(&token_list, ft_lstnew(convert_token(token)));
	else
		free(token);
	return (token_list);
}
