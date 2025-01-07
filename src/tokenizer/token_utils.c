/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:45:58 by dukim             #+#    #+#             */
/*   Updated: 2025/01/08 00:27:14 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_bool	is_specital_tokench(char ch)
{
	if (ch == ' ' || ch == '|' || ch == '>' || ch == '<')
		return (true);
	return (false);
}

void	append_token_inlist(t_list **tokenlst, t_word *word, \
							t_token_type type, t_envval *env_val)
{
	t_token	*token;
	size_t	i;

	i = -1;
	if (word->idx == 0)
		return ;
	convert_wordcotent(word, i);
	dollar_parser(word, env_val);
	token = malloc(sizeof(t_word) * 1);
	token->content = word->content;
	token->type = type;
	ft_lstadd_back(tokenlst, ft_lstnew(token));
	init_word(word);
}

void	free_token(void *ptr)
{	
	t_token	*token;

	token = (t_token *)ptr;
	free(token->content);
	free(token);
}
