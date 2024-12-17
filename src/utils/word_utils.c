/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:20:14 by dukim             #+#    #+#             */
/*   Updated: 2024/12/16 20:20:15 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define WORD_LEN 64

void	init_word(t_word *word)
{
	word->idx = 0;
	word->max_len = WORD_LEN;
	word->content = ft_calloc(sizeof(char), WORD_LEN + 1);
}

void	append_ch_inword(t_word *word, char ch)
{
	char	*extend;

	if (word->idx == word->max_len)
	{
		word->max_len *= 2;
		extend = ft_calloc(sizeof(char), word->max_len + 1);
		ft_strlcpy(extend, word->content, word->max_len / 2 + 1);
		free(word->content);
		word->content = extend;
	}
	word->content[word->idx++] = ch;
}

void	append_str_inword(t_word *word, char *str)
{
	while (*str)
	{
		append_ch_inword(word, *str);
		str++;
	}
}

void	append_token_inlist(t_list **token_list, t_word *token)
{
	if (token->idx == 0)
		return ;
	convert_wordcotent(token);
	ft_lstadd_back(token_list, ft_lstnew(token->content));
	init_word(token);
}
