/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/26 19:53:37 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Gère les états des quotes (simple et double)
void	update_quote_state(const char *line, int *in_single, int *in_double, int i)
{
	if (line[i] == '\'' && *in_double == 0)
		*in_single = !(*in_single);
	else if (line[i] == '"' && *in_single == 0)
		*in_double = !(*in_double);
}

// Ajoute une variable développée au buffer
void	handle_variable(const char *line, int *i, t_parse *parse)
{
	char	*var;
	int		k;

	if (line[*i + 1] == '?') // Cas de $?
	{
		var = ft_itoa(g_data.exit_code);
		g_data.exit_code = 0;
		(*i)++;
	}
	else if (line[*i + 1] == '$') // Cas de $$
	{
		var = ft_itoa(getpid());
		(*i)++;
	}
	else if (ft_isalnum(line[*i + 1]))
		var = parse_var(line, i);// Cas de $VAR
	k = 0;
	while (var[k])
		append_char(parse, var[k++]);
	free(var);
}

// Fonction principale de parsing de token
char	*parse_token(const char *line, int *i)
{
	t_parse	parse;
	int		in_single;
	int		in_double;

	init_parse(&parse, 256);
	in_single = 0;
	in_double = 0;
	while (line[*i] && (in_single || in_double || !ft_isspace(line[*i])))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			update_quote_state(line, &in_single, &in_double, *i);
		else if (line[*i] == '$' && in_single == 0)
			handle_variable(line, i, &parse);
		else if (line[*i] == '\\' && in_single == 0)
		{
			(*i)++;
			if (line[*i])
				append_char(&parse, line[*i]);
		}
		else
			append_char(&parse, line[*i]);
		if ((*i) <= (int)ft_strlen(line))
			(*i)++;
	}
	return (parse.buffer);
}
