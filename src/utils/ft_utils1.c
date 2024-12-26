/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:48:57 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 19:48:59 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bool	is_quote_ch(char ch)
{
	if (ch == '\'' || ch == '"')
		return (true);
	return (false);
}

t_bool	is_specital_ch(char ch)
{
	if (ch == ' '|| ch == '|' || ch == '>' || ch == '<')
		return (true);
	return (false);
}

char	**ft_lst_toarray(t_list *lst)
{
	char	**array;
	size_t	i;
	
	array = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		array[i++] = ft_strdup((const char *)lst->content);
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}
