/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 17:30:50 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_var(const char *token, int *index, t_data *data)
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

void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

char	**parse_args(char *str, t_data *data)
{
	char	**tokens;
	char	*token;
	int		i;
	int		count;

	if (!str || check_unclosed_quotes(str))
		return (write(2, "Error: unclosed quotes\n", 23), NULL);
	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i])
		{
			token = parse_token(str, &i, data);
			if (!token)
				return (free_tokens(tokens), NULL);
			tokens[count++] = token;
		}
	}
	tokens[count] = NULL;
	return (tokens);
}
