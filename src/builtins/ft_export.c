/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:12:55 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/31 16:32:20 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_bool	is_valid_exportname(char *name)
{
	int	p;

	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
	{
		printf("\'%s\' : not valid identifier!!\n", name);
		return (false);
	}
	p = 0;
	while (name[p])
	{
		if ((ft_isalnum(name[p]) == 0 && name[p] != '_') || name[p] == '=')
		{
			// if ((((name[p] == '+' && name[p + 1] != '=')))) // TODO: += 연산
			if (((name[p] == '+' && name[p + 1] == '=')) \
				|| (name[p] == '=' && name[p - 1] != '\0'))
				return (true);
			printf("\'%s\' : not valid identifier@@\n", name);
			return (false);
		}
		p++;
	}
	return (true);
}

static t_env	*create_env_node(char *envvalue)
{
	t_env	*node;
	char	**temp;

	node = (t_env *)malloc(sizeof(t_env));
	temp = ft_strdivide(envvalue, '=');
	node->key = temp[0];
	node->value = temp[1];
	free(temp);
	return (node);
}

static t_bool	check_overlapname(char *key, char *value, t_list *lst)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (ft_strncmp(key, env->key, ft_strlen(key) + 1) == 0)
		{
			if (env->value)
				free(env->value);
			if (value)//export _ 입력할때 오류수정
				env->value = ft_strdup(value);
			else
				env->value = ft_strdup("");//export 쓰레기갑처리
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

static void	append_envvalue(char **cmds, t_list *env_list, t_bool *is_changed)
{
	t_env	*node;
	int		i;

	i = 0;
	while (cmds[++i])
	{
		if (!is_valid_exportname(cmds[i]))
			continue;
		*is_changed = true;
		node = create_env_node(cmds[i]);
		if (check_overlapname(node->key, node->value, env_list))
			free_env(node);
		else
			ft_lstadd_back(&env_list, ft_lstnew(node));
	}
}

void	ft_export(char **cmds, t_envval *env_val)
{
	t_list	*ptr;
	t_env	*env;
	
	if (cmds[1] == NULL)
	{
		ptr = env_val->lst;
		while (ptr)
		{
			env = ptr->content;
			if (!(ft_strlen(env->key) == 1 && ft_strncmp(env->key, "_", 1) == 0))
			{
				printf("declare -x %s", env->key);
				if (env->value != NULL)
					printf("=\"%s\"", env->value);
				printf("\n");
			}
			ptr = ptr->next;
		}
	}
	else
		append_envvalue(cmds, env_val->lst, &(env_val->is_changed));
}
