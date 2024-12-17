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

static int	specitalch_handler(t_list **token_list, char **line, t_word *word)
{
	if (is_quote_ch(**line))
	{
		quote_parser(line, word);
		if (!word->content)
			return (-1);
	}
	else if (**line == ' ')
		append_token_inlist(token_list, word);
	else if (is_specital_ch(**line))
	{
		append_token_inlist(token_list, word);
		ft_lstadd_back(token_list, ft_lstnew(ft_substr(*line, 0, 1)));
	}
	else
		return (1);
	return (0);
}

void	convert_wordcotent(t_word *word)
{
	char	*pre;
	char	quote;
	size_t	i;

	pre = word->content;
	init_word(word);
	quote = 0;
	i = -1;
	while(pre[++i])
	{
		if (is_quote_ch(pre[i]))
		{
			if (quote == 0)
				quote = pre[i];
			else if (quote == pre[i])
				quote = 0;
			else
				append_ch_inword(word, pre[i]);
		}
		else if (pre[i] == '$' && quote != '\'')
			dollar_parser(word, pre, &i);
		else
			append_ch_inword(word, pre[i]);
	}
	free(pre);
}

t_list	*tokenizer(char *line)
{
	t_list	*token_list;
	t_word	*word;
	int		res;

	token_list = NULL;
	word = malloc(sizeof(t_word) * 1);
	init_word(word);
	while (*line)
	{
		res = specitalch_handler(&token_list, &line, word);
		if (res == -1)
		{
			ft_lstclear(&token_list, free);
			break ;
		}
		if (res == 1)
			append_ch_inword(word, *line);
		line++;
	}
	append_token_inlist(&token_list, word);
	free(word->content);
	free(word);
	return (token_list);
}
