/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:12:55 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/26 18:11:10 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_exportname(char *name)
{
	int	p;

	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
	{
		printf("\'%s\' : not valid identifier!!\n", name);
		return (-1);
	}
	p = 0;
	while (name[p])
	{
		if ((ft_isalnum(name[p]) == 0 && name[p] != '_') || name[p] == '=')
		{
			if ((((name[p] == '+' && name[p + 1] != '='))))
				;
			else if (((name[p] == '+' && name[p + 1] == '=')))
				return (0);
			else if ((name[p] == '=' && name[p - 1] != '\0'))
				return (0);
			printf("\'%s\' : not valid identifier@@\n", name);
			return (-1);
		}
		p++;
	}
	return (0);
}

static void	print_export(char **cmds, t_list *env_list)
{
	int     i;
	t_env  *list;

	i = 0;
	while (env_list)
	{
		list = env_list->content;
		if (!(ft_strlen(list->key) == 1 && ft_strncmp(list->key, "_", 1) == 0))
		{
			printf("declare -x %s", list->key);
			if (list->value != NULL)
				printf("=\"%s\"", list->value);
			printf("\n");
		}
		env_list = env_list->next;
	}
}

static t_env	*add_node(char *envvalue)
{
	t_env	*node;
	char	**temp;
	char	*tmp;

	node = (t_env *)malloc(sizeof(t_env));
	tmp = ft_strchr(envvalue, '=');
	if (tmp)
	{
		temp = ft_split(envvalue, '=');
		node->key = ft_strdup(temp[0]);
		node->value = ft_strdup(tmp + 1);
		ft_freesplit(temp);
	}
	else
	{
		node->key = ft_strdup(envvalue);
		node->value = NULL;
	}
	return (node);
}

static int	check_overlap(char *key, char *value, t_list *head)
{
	t_env	*cur;

	while (head)
	{
		cur = head->content;
		if (ft_strncmp(key, cur->key, ft_strlen(cur->key)) == 0 && \
		ft_strncmp(key, cur->key, ft_strlen(key)) == 0)
		{
			free(cur->value);
			cur->value = value;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static void	append_envvalue(char **cmds, t_list *env_list, t_bool *is_changed)
{
	t_env	*cur;
	int		i;

	i = 0;
	while (cmds[++i])
	{
		if (check_exportname(cmds[i]) == -1)
			continue;
		*is_changed = true;
		cur = add_node(cmds[i]);
		if (check_overlap(cur->key, cur->value, env_list) == 0)
			ft_lstadd_back(&env_list, ft_lstnew(cur));
		else
		{
			free(cur->key);
			free(cur->value);
			free(cur);
		}
	}
}

void	ft_export(char **cmds, t_envval *env_val)
{
	if (cmds[1] == NULL)
		print_export(cmds, env_val->lst);
	else
		append_envvalue(cmds, env_val->lst, &(env_val->is_changed));
}