/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 21:19:33 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(const char *env, t_list *env_list)
{
	size_t	len;

	len = ft_strlen(env);
	while (env_list)
	{
		if (ft_strncmp(((t_env *)env_list->content)->key, env, len +1) == 0)
			return (((t_env *)env_list->content)->value);
		env_list = env_list->next;
	}	
	return (NULL);
}

void	replace_envvalue(const char *env, char *replace, t_list *env_list)
{
	t_list	*ptr;
	size_t	len;

	len = ft_strlen(env);
	while (env_list)
	{
		if (ft_strncmp(((t_env *)env_list->content)->key, env, len +1) == 0)
		{
			free(((t_env *)env_list->content)->value);
			((t_env *)env_list->content)->value = ft_strdup(replace);
			return ;
		}
		env_list = env_list->next;
	}	
}

t_list	*init_env_list(char **envp)
{
	t_list  *env_list;
	t_env	*node;
	int		i;
	char	**temp;

	env_list = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = (t_env *)malloc(sizeof(t_env));
		temp = ft_strdivide(envp[i], '=');
		node->key = temp[0];
		node->value = temp[1];
		i++;
		ft_lstadd_back(&env_list, ft_lstnew(node));
		free(temp);
	}
	return (env_list);
}

void	free_env(void *ptr)
{
	t_env	*env;

	env = (t_env *)ptr;
	free(env->key);
	free(env->value);
	free(env);
}

char	**convert_lst_toenvp(t_envval *env_val)
{
	size_t	i;
	char	*temp;
	t_list	*ptr;

	if (!env_val->is_changed)
		return (env_val->envp);
	if (!env_val->envp)
		ft_freesplit(env_val->envp);
	env_val->envp = malloc(sizeof(char *) * (ft_lstsize(env_val->lst) + 1));
	i = 0;
	ptr = env_val->lst;
	while (ptr)
	{
		temp = ft_strjoin(((t_env *)ptr->content)->key, "=");
		env_val->envp[i++] = ft_strjoin(temp, ((t_env *)ptr->content)->value);
		free(temp);
		ptr = ptr->next;
	}
	env_val->envp[i] = NULL;
	env_val->is_changed = false;
	return (env_val->envp);
}