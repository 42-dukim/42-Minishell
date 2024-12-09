/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:45:38 by dukim             #+#    #+#             */
/*   Updated: 2024/12/06 19:45:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*quote_parser(char *line)
{
	char	*new_line;
	char	*temp;
	char	quote;
	size_t	len;
	size_t	i, j;

	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	quote = '\0';
	while (i < len)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (!quote)
				quote = line[i];
			else if (quote == line[i])
			{
				if (quote == '\'')
				{
					
				}
				if (quote == '"')
				{
					
				}
				quote = '\0';
			}
		}
		else
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = NULL;
	temp = new_line;
	new_line = ft_strdup(new_line);
	free(temp);
	return (new_line);
}