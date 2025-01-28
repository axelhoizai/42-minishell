/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 10:53:47 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_process_id(void)
{
	int		fd;
	char	buffer[32];
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buffer, 31) <= 0)
	{
		close(fd);
		return (-1);
	}
	buffer[31] = '\0';
	pid = ft_atoi(buffer);
	close(fd);
	return (pid);
}

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

	var = NULL;
	if (line[*i + 1] == '?') // for $?
	{
		var = ft_itoa(g_data.exit_code);
		g_data.exit_code = 0;
		(*i)++;
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

//replace
// while (line[*i] == '\\')
// 	(*i)++;
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
	while (line[*i] == '\\')
		(*i)++;
}

char	*parse_token(const char *line, int *i)
{
	t_parse	parse;

	init_parse(&parse, 256);
	while (line[*i] && (parse.in_single || parse.in_double || !ft_isspace(line[*i])))
	{
		if ((line[*i] == '\'' && parse.in_double == 0) || (line[*i] == '"' && parse.in_single == 0))
		{
			update_quote_state(line, &parse.in_single, &parse.in_double, *i);
			(*i)++;
			continue ;
		}
		handle_parse_token(line, i, &parse);
		if (line[*i] == '$' && parse.in_single == 0)
		{
			handle_variable(line, i, &parse);
			continue ;
		}
		append_char(&parse, line[*i]);
		(*i)++;
	}
	return (parse.buffer);
}
