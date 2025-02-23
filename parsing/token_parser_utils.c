/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:21:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 13:23:09 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_argv(t_argv *argv, int capacity)
{
	if (!argv)
		return ;
	argv->tokens = ft_calloc(capacity, sizeof(char *));
	argv->token_count = 0;
	argv->token_capacity = capacity;
}

void	free_argv(t_argv *argv)
{
	int	i;

	if (!argv || !argv->tokens)
		return ;
	i = 0;
	while (i < argv->token_count)
	{
		free(argv->tokens[i]);
		i++;
	}
	free(argv->tokens);
}

bool	chck_redir_pip(char *line, int *i)
{
	if (!line || !i || !line[*i] || !line[*i + 1])
		return (false);
	if (line[*i] == '>' && line[*i + 1] == '|' && line[*i + 2] != '|')
	{
		line[*i + 1] = '>';
		(*i)++;
		return (true);
	}
	return (false);
}

char	*parse_token(char *line, int *i, t_data *data)
{
	t_parse	parse;

	init_parse(&parse, 256);
	while (line[*i] && !ft_isspace(line[*i]))
	{
		(void)data;
		if (*i > 0 && (line[*i] == '|' && ft_strncmp(line, "export", 6) != 0))
			return (parse.buffer);
		if (line[*i] == '<' && line[*i + 1] != '<')
		{
			append_char(&parse, line[*i]);
			(*i)++;
			return (parse.buffer);
		}
		if (chck_redir_pip(line, i))
			continue ;
		(*i)++;
	}
	return (parse.buffer);
}

char	*skip_pips(char *str, int *i)
{
	char	*token;

	token = NULL;
	if ((str[*i] == '|' && str[*i + 1] == '|')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
	{
		token = ft_substr(str, *i, 2);
		*i += 2;
	}
	else if (str[*i] == '<' && str[*i + 1] == '|')
	{
		token = ft_calloc(2, 1);
		token[0] = str[*i];
		(*i)++;
	}
	else if ((str[*i] == '>' || str[*i] == '|') && str[*i + 1] != '|')
	{
		token = ft_calloc(2, 1);
		token[0] = str[*i];
		(*i)++;
	}
	return (token);
}
