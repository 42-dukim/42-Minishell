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

void	append_token_inlist(t_list **token_list, t_word *word, t_token_type type)
{
	t_token	*token;

	if (word->idx == 0)
		return ;
	convert_wordcotent(word);
	token = malloc(sizeof(t_word) * 1);
	token->content = word->content;
	token->type = type;
	ft_lstadd_back(token_list, ft_lstnew(token));
	init_word(word);
}

t_token_type	get_tokentype(char ch)
{
	if (ch == '>' || ch == '<')
		return (REDI);
	if (ch == '|')
		return (PIPE);
}

char	**tokenlst_to_array(t_list *list)
{
	char	**array;
	t_list	*ptr;
	t_list	*temp;
	size_t	i;

	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	ptr = list;
	i = 0;
	while (ptr)
	{
		array[i++] = ((t_token *)ptr->content)->content;
		temp = ptr->next;
		free(ptr->content);
		free(ptr);
		ptr = temp;
	}
	array[i] = NULL;
	return (array);
}