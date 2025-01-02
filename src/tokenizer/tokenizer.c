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

static void	word_tosymbol(char **line, t_word *word, char symbol)
{
	if (ft_strncmp(*line, ">>", 2) == 0)
	{
		symbol = '+';
		(*line)++;
	}
	if (ft_strncmp(*line, "<<", 2) == 0)
	{
		symbol = '-';
		(*line)++;
	}
	free(word->content);
	word->content = malloc(sizeof(char) * 2);
	word->content[0] = symbol;
	word->content[1] = '\0';
	word->idx = 1;
}

static int	specitalch_handler(t_list **token_list, char **line, t_word *word, t_list *env_list)
{
	char	ch;

	ch = **line;
	if (is_quote_ch(ch))
	{
		quote_parser(line, word);
		if (!word->content)
			return (-1);
	}
	else if (is_specital_tokench(ch))
	{
		append_token_inlist(token_list, word, WORD, env_list);
		if (ch != ' ')
		{
			word_tosymbol(line, word, ch);
			append_token_inlist(token_list, word, SYMBOL, env_list);
		}
	}
	else
		return (1);
	return (0);
}

t_list	*tokenizer(char *line, t_list *env_list)
{
	t_list	*token_list;
	t_word	*word;
	int		res;

	token_list = NULL;
	word = malloc(sizeof(t_word) * 1);
	init_word(word);
	while (*line)
	{
		res = specitalch_handler(&token_list, &line, word, env_list);
		if (res == -1)
		{
			ft_lstclear(&token_list, free);
			break ;
		}
		if (res == 1)
			append_ch_inword(word, *line);
		line++;
	}
	append_token_inlist(&token_list, word, WORD, env_list);
	free(word->content);
	free(word);
	return (token_list);
}
