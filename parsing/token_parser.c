/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/19 18:01:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_quote_state(const char *line, int *in_s, int *in_d, int i)
{
	if (line[i] == '\'' && *in_d == 0)
		*in_s = !(*in_s);
	else if (line[i] == '"' && *in_s == 0)
		*in_d = !(*in_d);
}

//to use \ escape char
// if (line[*i] == '\\' && parse->in_single == 0)
// {
// 	(*i)++;
// 	if (line[*i])
// 		append_char(parse, line[*i]);
// 	(*i)++;
// }

static void	handle_parse_token(const char *line, int *i, t_parse *parse)
{
	if ((line[*i] == '\'' && parse->in_double)
		|| (line[*i] == '"' && parse->in_single))
	{
		append_char(parse, line[*i]);
		(*i)++;
	}
}

static void	check_closing_quote(char *line, int *i, t_parse *parse)
{
	if (line[*i] && (((line[*i] == '\'' && parse->in_double == 1)
				|| (line[*i] == '"' && parse->in_single == 1))
			|| (line[*i] != '"' && line[*i] != '\'')))
		append_char(parse, line[*i]);
}

//? Big function handling parsing
char	*parse_token(char *line, int *i, t_data *data, char	**tokens)
{
	t_parse	parse;

	init_parse(&parse, 256);
	while (line[*i] && (parse.in_single || parse.in_double
			|| !ft_isspace(line[*i])))
	{
		if (*i > 0 && line[*i] == '|' && tokens[0] && ft_strcmp(tokens[0], "export") != 0) 
			return (parse.buffer);
		if (line[*i] == '>' && line[*i + 1] == '|')
		{
			line[*i + 1] = '>';
			(*i)++;
			continue ;
		}
		if ((line[*i] == '\'' && parse.in_double == 0)
			|| (line[*i] == '"' && parse.in_single == 0))
		{
			update_quote_state(line, &parse.in_single, &parse.in_double, *i);
			(*i)++;
			continue ;
		}
		handle_parse_token(line, i, &parse);
		if (line[*i] == '$' && parse.in_single == 0
			&& (ft_isalnum(line[*i + 1])
				|| line[*i + 1] == '?' || line[*i + 1] == '$'))
		{
			handle_variable(line, i, &parse, data);
			continue ;
		}
		check_closing_quote(line, i, &parse);
		(*i)++;
	}
	return (parse.buffer);
}
