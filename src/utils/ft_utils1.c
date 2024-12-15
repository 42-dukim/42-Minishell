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

char	*ft_strreplace(char *str, size_t start, size_t end, char *replace)
{
	char	*temp1;
	char	*temp2;

	str[start - 1] = '\0';
	temp1 = ft_strjoin(str, replace);
	temp2 = ft_strjoin(temp1, str + end);
	free(str);
	free(temp1);
	return (temp2);
}

void	ft_strsplice(char *str, size_t start, size_t end)
{
	ft_strlcpy(str + start, str + end + 1, ft_strlen(str) - end + 1);
}