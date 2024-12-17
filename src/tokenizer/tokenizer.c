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

#include "tokenizer.h"

static int	specitalch_handler(t_list **token_list, char **line, t_word *word)
{
	if (is_quote_ch(**line))
	{
		quote_parser(line, word);
		if (!word->content)
			return (-1);
	}
	else if (is_specital_ch(**line))
	{
		append_token_inlist(token_list, word, WORD);
		if (**line != ' ')
		{
			free(word->content);
			word->content = ft_substr(*line, 0, 1);
			word->idx = 1;
			append_token_inlist(token_list, word, get_tokentype(**line));
		}
	}
	else
		return (1);
	return (0);
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
	append_token_inlist(&token_list, word, WORD);
	free(word->content);
	free(word);
	return (token_list);
}
