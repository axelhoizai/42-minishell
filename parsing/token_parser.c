/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/31 17:57:31 by ahoizai          ###   ########.fr       */
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
	return (var);
}

static void	handle_variable(char *line, int *i, t_parse *parse, t_data *data)
{
	char	*var;
	int		k;

	var = NULL;
	if (line[*i + 1] == '?' || line[*i + 1] == '$')
		var = handle_special_var(line, i, data);
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

//? Big function handling parsing
char	*parse_token(char *line, int *i, t_data *data)
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
		if (line[*i] == '$' && parse.in_single == 0
			&& (ft_isalnum(line[*i + 1])
				|| line[*i + 1] == '?' || line[*i + 1] == '$'))
		{
			handle_variable(line, i, &parse, data);
			continue ;
		}
		append_char(&parse, line[*i]);
		(*i)++;
	}
	return (parse.buffer);
}
