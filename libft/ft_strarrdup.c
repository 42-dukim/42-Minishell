/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:59:19 by dukim             #+#    #+#             */
/*   Updated: 2024/11/30 00:59:20 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrdup(char **strarr)
{
	char	**dup;
	size_t	len;
	size_t	i;

	len = ft_splitlen((const char **)strarr);
	dup = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		dup[i] = ft_strdup(strarr[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
