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
