/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:07:06 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/13 17:53:58 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;

int     ft_export(char **cmds)
{
        t_list  *node;
        int     i;

        i = 0;
        if (cmds[++i])
        {
                node = (t_list *)g_data.export;
                while (node)
                {
                        printf("declare -x %p\n", node->content);
                        node = node->next;
                }
                return (0);
        }
        // else        
        //         node = g_data.export;
        //         node->content;
        //         node->size;
        //         node->next;
        return (0);
}