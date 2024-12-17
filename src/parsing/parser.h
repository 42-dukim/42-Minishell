/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:16:55 by dukim             #+#    #+#             */
/*   Updated: 2024/12/18 03:16:57 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../inc/minishell.h"

typedef struct s_tree_node
{
	void				*token;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

#endif