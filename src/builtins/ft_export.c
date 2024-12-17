/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:12:55 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/17 21:19:20 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_global	g_data;


void	insert_sorted(t_list **sorted_head, t_list *new_node)
{
	t_list	*cur;

	if (*sorted_head == NULL || (ft_strncmp((*sorted_head)->content, new_node->content, ft_strlen(new_node->content)) >= 0))
	{
		new_node->next = *sorted_head;
		*sorted_head = new_node;
	}
	else
	{
		cur = *sorted_head;
		while (cur->next != NULL && (ft_strncmp(cur->next->content, new_node->content, ft_strlen(new_node->content)) < 0))
			cur = cur->next;
		new_node->next = cur->next;
		cur->next = new_node;
	}
}
int     check_exportname(char *name)
{
	int	i;

	if (ft_isdigit(name[0]) == 1 && ft_isalpha(name[0]) == 0 && name[0] != '_')
	{
		printf("\'%s\' : not valid identifier\n!!", name);
		return (-1);
	}
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			printf("\'%s\' : not valid identifier@@\n", name);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	print_export(char **cmds)
{
	t_list	*export_list;
	int		i;

	i = 0;
	export_list = g_data.link_envp->var;
	while (export_list->next)
	{
		if (!(ft_strlen(export_list->content) == 1 && ft_strncmp(export_list->content, "_", 1) == 0))
			printf("declare -x %s\n", (char *)export_list->content);
		export_list = export_list->next;
		i++;
	}
	return (0);
}

int    check_export(char **cmds, t_list *new)
{
	t_list	*current;
	char	*temp;

	if (g_data.envp == NULL)
		return (0);
	current = ft_lstnew(g_data.envp);
	while (current)
	{
		if (ft_strncmp(current->content, new->content, ft_strlen(new->content)) == 0)
		{
			temp = current->content;
			current->content = ft_strdup(new->content);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
void	node_back(t_list **head, t_list *new)
{
	t_list	*current;

	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new;
	}
}
void	value_export(char **cmds)
{
	t_list	*new;
	int		i;

	i = 0;
	while (cmds[i])
	{
		new = ft_lstnew(cmds[i]);
		if (check_exportname(new->content) == -1)
		{
				return ;
		}
		else if (check_export(cmds, new) == 0)
		{
			node_back(&g_data.link_envp->var, new);
		}
		i++;
	}
}

int	ft_export(char **cmds)
{
	if (cmds[1] == NULL)
		print_export(cmds);
	else
		value_export(cmds);
	return (0);
}