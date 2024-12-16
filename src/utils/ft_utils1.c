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

char	**ft_lstto_array(t_list *list)
{
	char	**array;
	t_list	*ptr;
	t_list	*temp;
	size_t	len;
	size_t	i;

	len = ft_lstsize(list);
	array = malloc(sizeof(char *) * (len + 1));
	ptr = list;
	i = 0;
	while (i < len)
	{
		array[i++] = ptr->content;
		temp = ptr->next;
		free(ptr);
		ptr = temp;
	}
	array[i] = NULL;
	return (array);
}

t_bool	is_quote_ch(char ch)
{
	if (ch == '\'' || ch == '"')
		return (true);
	return (false);
}