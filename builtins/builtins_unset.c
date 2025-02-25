/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:03:10 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/25 11:47:53 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chck_identifier_unset(char *id, t_data *data, int *i)
{
	char	*index;

	index = ft_substr(id, 0, find_index(id));
	if (ft_isdigit(index[0]) || ft_strchr(index, '-') || ft_strchr(index, '.')
		|| ft_strchr(index, '}') || ft_strchr(index, '{')
		|| ft_strchr(index, '*') || ft_strchr(index, '#')
		|| ft_strchr(index, '@') || ft_strchr(index, '+')
		|| ft_strchr(index, '!') || ft_strchr(index, '%')
		|| !ft_strcmp(index, "=") || index[0] == '=' 
		|| ft_strchr(index, '?' ))
	{
		ft_print_error("unset", id, "not a valid identifier");
		data->exit_code = 1;
		(*i)++;
	}
	free(index);
}

void	ft_unset(char **argv, t_data *data)
{
	int		i;
	char	*key;

	if (!ft_strcmp(argv[0], "export"))
	{
		i = 1;
		while (argv[i])
		{
			key = get_envkey(argv[i]);
			ms_lstdelone(&data->env_ms, key);
			free(key);
			i++;
		}
	}
	else if (argv[1])
	{
		i = 1;
		chck_identifier_unset(argv[i], data, &i);	
		while (argv[i])
		{
			ms_lstdelone(&data->env_ms, argv[i]);
			i++;
		}
	}
	lst_to_tab(data->env_ms, data);
}
