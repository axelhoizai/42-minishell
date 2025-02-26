/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 13:24:14 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote_state(const char *line, int *in_s, int *in_d, int i)
{
	if (line[i] == '\'' && *in_d == 0)
		*in_s = !(*in_s);
	else if (line[i] == '"' && *in_s == 0)
		*in_d = !(*in_d);
}

static void	check_closing_quote(char *line, int *i, t_parse *parse)
{
	if (line[*i] && (((line[*i] == '\'' && parse->in_double == 1)
				|| (line[*i] == '"' && parse->in_single == 1))
			|| (line[*i] != '"' && line[*i] != '\'')))
		append_char(parse, line[*i]);
	update_quote_state(line, &(parse->in_single), &(parse->in_double), *i);
}

static bool	chck_quote_state(char *line, int *i, t_parse *parse)
{
	if ((line[*i] == '\'' && parse->in_double == 0)
		|| (line[*i] == '"' && parse->in_single == 0))
	{
		update_quote_state(line, &(parse->in_single), &(parse->in_double), *i);
		(*i)++;
		return (true);
	}
	return (false);
}

static void	handle_parse_token(const char *line, int *i, t_parse *parse)
{
	if ((line[*i] == '\'' && parse->in_double)
		|| (line[*i] == '"' && parse->in_single))
	{
		append_char(parse, line[*i]);
		(*i)++;
	}
}

char	*parse_lexer(char *line, int *i, t_data *data)
{
	t_parse	parse;

	if (line[*i] && line[*i + 1] && line[*i] == '$'
		&& (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		(*i)++;
	init_parse(&parse, 256);
	while (line && line[*i] && (parse.in_single || parse.in_double
			|| !ft_isspace(line[*i])))
	{
		(void)data;
		if (chck_quote_state(line, i, &parse))
			continue ;
		handle_parse_token(line, i, &parse);
		if (handle_check_var(line, i, data, &parse))
			continue ;
		check_closing_quote(line, i, &parse);
		(*i)++;
	}
	return (parse.buffer);
}
