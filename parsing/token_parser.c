/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 17:59:59 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Gère les états des quotes (simple et double)
void	update_quote_state(const char *line, int *in_s, int *in_d, int i)
{
	if (line[i] == '\'' && *in_d == 0)
		*in_s = !(*in_s);
	else if (line[i] == '"' && *in_s == 0)
		*in_d = !(*in_d);
}

// Ajoute une variable développée au buffer
void	handle_variable(const char *line, int *i, t_parse *parse)
{
	char	*var;
	int		k;

	var = NULL;
	if (line[*i + 1] == '?') // for $?
	{
		var = ft_itoa(g_data.exit_code);
		g_data.exit_code = 0;
		(*i)+= 2;
	}
	else if (line[*i + 1] == '$') //for $$
	{
		var	= ft_itoa(get_process_id());
		(*i)+= 2;
	}
	else if (ft_isalnum(line[*i + 1]) || line[*i] == '_')
	{
		var = parse_var(line, i);// for $VAR
		(*i)++;
	}
	k = 0;
	while (var[k])
		append_char(parse, var[k++]);
	free(var);
}

//to use \ escape char
// if (line[*i] == '\\' && parse->in_single == 0)
// {
// 	(*i)++;
// 	if (line[*i])
// 		append_char(parse, line[*i]);
// 	(*i)++;
// }
void	handle_parse_token(const char *line, int *i, t_parse *parse)
{
	if ((line[*i] == '\'' && parse->in_double)
		|| (line[*i] == '"' && parse->in_single))
	{
		append_char(parse, line[*i]);
		(*i)++;
	}
}

char	*parse_token(const char *line, int *i)
{
	t_parse	parse;

	init_parse(&parse, 256);
	while (line[*i] && (parse.in_single || parse.in_double
		|| !ft_isspace(line[*i])))
	{
		if ((line[*i] == '\'' && parse.in_double == 0)
			|| (line[*i] == '"' && parse.in_single == 0))
		{
			update_quote_state(line, &parse.in_single, &parse.in_double, *i);
			(*i)++;
			continue ;
		}
		handle_parse_token(line, i, &parse);
		if (line[*i] == '$'  && parse.in_single == 0
			&& (ft_isalnum(line[*i + 1])
			|| line[*i + 1] == '?' || line[*i + 1] == '$'))
		{
			handle_variable(line, i, &parse);
			continue ;
		}
		append_char(&parse, line[*i]);
		(*i)++;
	}
	return (parse.buffer);
}
