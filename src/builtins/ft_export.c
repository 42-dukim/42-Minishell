// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_export.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/15 16:12:55 by junkwak           #+#    #+#             */
// /*   Updated: 2024/12/16 18:28:12 by junkwak          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/minishell.h"

// extern t_global	g_data;


// void	insert_sorted(t_list **sorted_head, t_list *new_node)
// {
// 	t_list	*cur;

// 	if (*sorted_head == NULL || (ft_strcmp((*sorted_head)->content, new_node->content) >= 0))
// 	{
// 		new_node->next = *sorted_head;
// 		*sorted_head = new_node;
// 	}
// 	else
// 	{
// 		cur = *sorted_head;
// 		while (cur->next != NULL && (ft_strcmp(cur->next->content, new_node->content) < 0))
// 			cur = cur->next;
// 		new_node->next = cur->next;
// 		cur->next = new_node;
// 	}
// }
// int     check_exportname(char *name)
// {
//         int     i;

//         if (ft_isdigit(name[0]) == 1 && ft_isalpha(name[0]) == 0 && name[0] != '_')
//         {
//                 printf("\'%s\' : not valid identifier\n!!", name);
//                 return (-1);
//         }
//         i = 1;
//         while (name[i])
//         {
//                 if (ft_isalnum(name[i]) == 0 && name[i] != '_')
//                 {
//                         printf("\'%s\' : not valid identifier@@\n", name);
//                         return (-1);
//                 }
//                 i++;
//         }
//         return (0);
// }

// int	print_export(char **cmds, t_list *head)
// {
//         //t_list  *sorted;
//         t_list  *export_list;
//         //t_list  *head;
//         int     i;

//         i = 0;
// 	while (head->next)
// 	{
// 		if (!(ft_strlen(head->content) == 1 && ft_strncmp(head->content, "_", 1) == 0))
// 			printf("declare -x %s=\"%s\"\n", (char *)head->content, (char *)head->content);
// 		head = head->next;
//                 i++;
// 	}
// 	//free(head);
// 	return (0);
// }
// int    check_export(char **cmds, t_list *new)
// {
//         t_list  *current;
//         char    *temp;

//         if (g_data.envp == NULL)
//                 return (0);
//         current = ft_lstnew(g_data.envp);
//         while (current)
//         {
//                 if (ft_strcmp(current->content, new->content) == 0)
//                 {
//                         temp = current->content;
//                         current->content = ft_strdup(new->content);
//                         free(new);
//                         free(temp);
//                         return (1);
//                 }
//                 current = current->next;
//         }
//         return (0);
// }
// void    node_back(t_list *head, t_list *new)
// {
//         t_list  *current;

//         if (head == NULL)
//                 head = new;
//         else
//         {
//                 current = head;
//                 while (current->next)
//                 {
//                         current = current->next;
//                 }
//                 current->next = new;
//         }
// }
// void    value_export(char **cmds,t_list *head)
// {
//         t_list  *new;
//         //t_list  *head;
//         int     i;

//         i = 0;
//         // head = (t_list *)g_data.export;
//         // head = ft_lstnew(g_data.export);
//         while (cmds[i])
//         {
//                 new = ft_lstnew(cmds[i]);
//                 if (check_exportname(new->content) == -1)
//                 {
//                         //free(new);
//                 }
//                 else if (check_export(cmds, new) == 0)
//                 {
//                         node_back(head, new);
//                 }
//                 i++;
//         }
// }


// t_list *arry_list(t_list *head)
// {
//         char **env;
//         int i = 0;
//         t_list *new;
//         // t_list *head;

//         env = g_data.envp;
//         head = NULL;
//         if (head == NULL)
//         {
//                 new = ft_lstnew(env[i]);
//                 head = new;
//                 i++;
//         }
//         while (env[i])
//         {
//                 new = ft_lstnew(env[i]);
//                 if (check_exportname(new->content) == -1)
//                 {
//                         free(new);
//                 }
//                 //insert_sorted(&head, new);
//                 if (check_export(env, new) == 0)
//                 {
//                         node_back(head, new);
//                 }
//                 i++;
//         }
//         return (head);
// }
// int     ft_export(char **cmds)
// {
//         t_list  *head;

//         g_data.export = arry_list(g_data.envp);
//         if (cmds[1] == NULL)
//                 print_export(cmds,g_data.export);
//         else
//                 value_export(cmds,g_data.export);
//         // else        
//         //         node = g_data.export;
//         //         node->content;
//         //         node->size;
//         //         node->next;
//         return (0);
// }
// // t_list	*sorted_envp_list(t_list *head)
// // {
// // 	// t_list	*sorted_head;
// // 	t_list	*cur;
// // 	t_list	*new;
        
// // 	// sorted_head = NULL;
// // 	cur = head;
// // 	while (cur != NULL)
// // 	{
// // 		new = ft_lstnew(cur->content);
// // 		insert_sorted(&head, new);
// // 		cur = cur->next;
// // 	}
// // 	return (head);
// // }