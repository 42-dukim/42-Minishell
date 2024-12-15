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

t_list	*tokenizer(char *line)
{
	t_list	*token_list;
	char	*token;
	size_t	token_len;
	size_t	i;

	token_list = NULL;
	line--;
	init_token(&token, &i, &token_len);
	while (*(++line))
	{
		if (*line == '\'' || *line == '"')	// qutoe parsing후에 ' ' 만날 때 또 parsing 과정 반복
		{
			token = quote_parser(&line, token);
			token_len = ft_strlen(token);
			i = token_len;
			continue ;
		}
		if (*line == ' ')
		{
			if (i == 0)
				continue ;
			ft_lstadd_back(&token_list, ft_lstnew(dollar_parser(token)));
			init_token(&token, &i, &token_len);
			continue ;
		}
		if (i == token_len)
			extend_str(&token, &token_len);
		token[i++] = *line;
	}
	if (i > 0)
		ft_lstadd_back(&token_list, ft_lstnew(dollar_parser(token)));
	else
		free(token);
	return (token_list);
}
