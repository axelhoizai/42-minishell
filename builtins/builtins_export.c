/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:02:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/20 19:16:00 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_env_ms *lst)
{
	t_env_ms	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (strcmp(tmp->key, "_") != 0)
		{
			if (tmp->equal_sign == true)
				ft_printf("export %s=\"%s\"\n", tmp->key, tmp->value);
			else
				ft_printf("export %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

int	find_index(char *str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str, "="))
		return (1);
	if (str[0] == '=')
		return (ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '=')
			return(i) ;
		i++;
	}
	return (i);
}

bool	chck_identifier(char *id, t_data *data)
{
	int		i;
	char	*index;
	
	i = 0;
	index = ft_substr(id, 0, find_index(id));
	if (ft_isdigit(index[0]) || ft_strchr(index, '-') || ft_strchr(index, '.')
		|| ft_strchr(index, '}') || ft_strchr(index, '{') 
		|| ft_strchr(index, '*') || ft_strchr(index, '#')
		|| ft_strchr(index, '@') || ft_strchr(index, '+')
		|| !ft_strcmp(index, "=") || index[0] == '=')
	{
		ft_print_error("export", id, "not a valid identifier");
		data->exit_code = 1;
		free(index);
		return (false);
	}
	free(index);
	return (true);
}

static void	add_var(char *key, char **argv, t_data *data)
{
	int			i;

	i = 1;
	while (argv[i] && argv[i][0] != '$')
	{
		if (!chck_identifier(argv[i], data))
			return ;
		key = get_envkey(argv[i]);
		printf("key : %s\n", key);
		ft_unset(argv, data);
		if (!ms_find(data->env_ms, key))
		{
			if (ft_strchr(argv[i], '='))
			{
				ms_lstadd_back(&(data->env_ms),
					ms_lstnew(get_envkey(argv[i]),
						get_envval(argv[i]), true));
			}
			else
			{
				ms_lstadd_back(&(data->env_ms),
					ms_lstnew(get_envkey(argv[i]),
						get_envval(argv[i]), false));
			}
		}
		free(key);
		i++;
	}
}

void	ft_export(char **argv, t_data *data)
{
	char	*key;

	key = NULL;
	if (ft_strcmp(argv[0], "export") == 0 && (!argv[1] || argv[1][0] == '\0'))
		print_export(data->env_ms);
	else if (ft_strcmp(argv[0], "export") == 0 && argv[1] && argv[1][0] != '$')
	{
		add_var(key, argv, data);
		lst_to_tab(data->env_ms, data);
	}
}

bool	is_key(t_env_ms *lst, char *var)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, var) == 0)
			return (true);
		lst = lst->next;
	}
	return (false);
}

t_env_ms	*ms_find(t_env_ms *lst, char *var)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, var) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
