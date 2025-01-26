/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/26 23:29:11 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_var(const char *token, int *index)
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
	if (is_key(g_data.env_ms, var_name))
	{
		to_find = ms_find(g_data.env_ms, var_name);
		if (to_find && to_find->value)
			value = to_find->value;
	}
	(*index)--;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

// Ajoute un token au tableau
int	add_token(const char *str, int *i, char **tokens, int token_count)
{
	char	*token;

	token = parse_token(str, i);
	if (!token)
		return (-1);
	tokens[token_count] = token;
	return (token_count + 1);
}

// Fonction principale pour parser les arguments
char	**parse_args(const char *str)
{
	char	**tokens;
	int		i;
	int		token_count;

	if (!str || check_unclosed_quotes(str))
	{
		write(2, "Error: unclosed quotes\n", 23);
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);
	i = 0;
	token_count = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i])
		{
			token_count = add_token(str, &i, tokens, token_count);
			if (token_count == -1)
				return (free_tokens(tokens), NULL);
		}
	}
	return (tokens[token_count] = NULL, tokens);
}
