/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 02:10:31 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	chck_redir_pip(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '|' && line[*i + 2] != '|')
	{
		line[*i + 1] = '>';
		(*i)++;
		return (true);
	}
	return (false);
}

static char	*parse_token(char *line, int *i, t_data *data)
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

static char	*skip_pips(char *str, int *i)
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

static bool	tokenize_string(char **tokens, int *count, t_data *data)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		while (tokens[i][j])
		{
			token = skip_pips(tokens[i], &j);
			token = parse_token(tokens[i], &j, data);
			if (!token)
				return (free_tab(tokens), false);
			tokens[(*count)++] = token;
		}
		i++;
	}
	// tokens[*count] = NULL;
	// if (*count == 0)
	// 	return (free_tokens(tokens), false);
	return (true);
}

//? Get the input and 
void	parse_argv(char **argv, int argc, t_data *data) //parsing
{
	//parsing pip ici
	tokenize_string(argv, &argc, data);
	print_tab(argv); //print_tab
	// if (argc > 0)
	// {
	// 	send_to_exec(argv, data);
	// 	return ;
	// }
}
