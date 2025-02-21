/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:07:40 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/21 17:29:01 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? Check if VAR is ok
static char	*parse_var(const char *token, int *index, t_data *data)
{
	char		var_name[256];
	const char	*value;
	int			j;
	t_env_ms	*to_find;

	(*index)++;
	j = 0;
	to_find = NULL;
	value = NULL;
	while (ft_isalnum(token[*index]) || token[*index] == '_')
		var_name[j++] = token[(*index)++];
	var_name[j] = '\0';
	if (is_key(data->env_ms, var_name))
	{
		to_find = ms_find(data->env_ms, var_name);
		if (to_find && to_find->value)
			value = to_find->value;
	}
	(*index)--;
	if (!value && ft_strcmp(var_name, "UID") == 0)
		return (get_uid());
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*handle_special_var(const char *line, int *i, t_data *data)
{
	char	*var;

	var = NULL;
	if (line[*i + 1] == '?')
	{
		var = ft_itoa(data->exit_code);
		data->exit_code = 0;
		(*i) += 2;
	}
	else if (line[*i + 1] == '$')
	{
		var = ft_itoa(get_process_id());
		(*i) += 2;
	}
	else if (line[*i + 1] == '0')
	{
		var = ft_strdup("minishell");
		(*i) += 2;
	}
	return (var);
}

static char	*handle_pwd_var(const char *line, int *i, t_data *data)
{
	char	*var;
	char	*tmp_line;

	tmp_line = ft_strdup(line);
	var = NULL;
	if (line[*i + 1] == 'O' && line[*i + 2] == 'L' && line[*i + 3] == 'D'
		&& line[*i + 4] == 'P' && line[*i + 5] == 'W' && line[*i + 6] == 'D')
	{
		var = ft_strdup(data->oldpwd);
		(*i) += 7;
	}
	else if (line[*i + 1] == 'P' && line[*i + 2] == 'W' && line[*i + 3] == 'D')
	{
		var = ft_strdup(data->pwd);
		(*i) += 4;
	}
	free(tmp_line);
	return (var);
}

void	handle_variable(char *line, int *i, t_parse *parse, t_data *data)
{
	char	*var;
	int		k;

	var = NULL;
	if (line[*i + 1] == '?' || line[*i + 1] == '$' || line[*i + 1] == '0')
		var = handle_special_var(line, i, data);
	else if (line[*i + 1] == 'P' || line[*i + 1] == 'O')
		var = handle_pwd_var(line, i, data);
	else if (ft_isdigit(line[*i + 1]))
	{
		(*i) += 2;
		return ;
	}
	else if ((ft_isalnum(line[*i + 1]) || line[*i] == '_'))
	{
		var = parse_var(line, i, data);
		(*i)++;
	}
	k = 0;
	while (var[k])
		append_char(parse, var[k++]);
	free(var);
}
