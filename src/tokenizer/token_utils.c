/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:45:58 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 21:46:00 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_bool	is_specital_tokench(char ch)
{
	if (ch == ' '|| ch == '|' || ch == '>' || ch == '<')
		return (true);
	return (false);
}

void	append_token_inlist(t_list **tokenlst, t_word *word, t_token_type type, t_list *env_list)
{
	t_token	*token;

	if (word->idx == 0)
		return ;
	convert_wordcotent(word, env_list);
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
