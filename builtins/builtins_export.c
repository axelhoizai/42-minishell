/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:02:47 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 14:24:05 by mdemare          ###   ########.fr       */
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

static bool	chck_identifier(char *id, t_data *data)
{
	char	*index;

	index = ft_substr(id, 0, find_index(id));
	if (ft_isdigit(index[0]) || ft_strchr(index, '-') || ft_strchr(index, '.')
		|| (id && ft_strlen(id) == 0)
		|| ft_strchr(index, '}') || ft_strchr(index, '{')
		|| ft_strchr(index, '*') || ft_strchr(index, '#')
		|| ft_strchr(index, '@') || ft_strchr(index, '+')
		|| ft_strchr(index, '!') || ft_strchr(index, '%')
		|| ft_strchr(index, '?') || ft_strchr(index, '~')
		|| !ft_strcmp(index, "=") || index[0] == '=')
	{
		ft_print_error("export", id, "not a valid identifier");
		data->exit_code = 1;
		free(index);
		return (false);
	}
	free(index);
	data->exit_code = 0;
	return (true);
}

static void	add_var(char *key, char *value, char **argv, t_data *data)
{
	int		i;

	i = 1;
	while (argv[i] && argv[i][0] != '$')
	{
		if (chck_identifier(argv[i], data))
		{
			key = get_envkey(argv[i]);
			if (ms_find(data->env_ms, key))
				ft_unset(argv, data);
			if (ft_strchr(argv[i], '='))
			{
				value = get_envval(argv[i]);
				ms_lstadd_back(&(data->env_ms), ms_lstnew(get_envkey(argv[i]),
						ft_strtrim(value, " 	"), true));
				free(value);
			}
			else
				ms_lstadd_back(&(data->env_ms), ms_lstnew(get_envkey(argv[i]),
						get_envval(argv[i]), false));
			free(key);
		}
		i++;
	}
}

void	ft_export(char **argv, t_data *data)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (ft_strcmp(argv[0], "export") == 0 && !argv[1])
	{
		print_export(data->env_ms);
		data->exit_code = 0;
	}
	else if (ft_strcmp(argv[0], "export") == 0 && argv[1] && argv[1][0] != '$')
	{
		add_var(key, value, argv, data);
		lst_to_tab(data->env_ms, data);
	}
}
