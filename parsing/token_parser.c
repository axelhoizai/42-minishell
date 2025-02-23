/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/22 19:42:06 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// static void	update_quote_state(const char *line, int *in_s, int *in_d, int i)
// {
// 	if (line[i] == '\'' && *in_d == 0)
// 		*in_s = !(*in_s);
// 	else if (line[i] == '"' && *in_s == 0)
// 		*in_d = !(*in_d);
// }

// //to use \ escape char
// // if (line[*i] == '\\' && parse->in_single == 0)
// // {
// // 	(*i)++;
// // 	if (line[*i])
// // 		append_char(parse, line[*i]);
// // 	(*i)++;
// // }

// static void	check_closing_quote(char *line, int *i, t_parse *parse)
// {
// 	if (line[*i] && (((line[*i] == '\'' && parse->in_double == 1)
// 				|| (line[*i] == '"' && parse->in_single == 1))
// 			|| (line[*i] != '"' && line[*i] != '\'')))
// 		append_char(parse, line[*i]);
// }

// bool	chck_redir_pip(char *line, int *i)
// {
// 	if (line[*i] == '>' && line[*i + 1] == '|' && line[*i + 2] != '|')
// 	{
// 		line[*i + 1] = '>';
// 		(*i)++;
// 		return (true);
// 	}
// 	return (false);
// }

// bool	chck_quote_state(char *line, int *i, t_parse *parse)
// {
// 	if ((line[*i] == '\'' && parse->in_double == 0)
// 		|| (line[*i] == '"' && parse->in_single == 0))
// 	{
// 		update_quote_state(line, &(parse->in_single), &(parse->in_double), *i);
// 		(*i)++;
// 		return (true);
// 	}
// 	return (false);
// }

// //? Big function handling parsing
// char	*parse_token(char *line, int *i, t_data *data)
// {
// 	t_parse	parse;

// 	init_parse(&parse, 256);
// 	while (line[*i] && (parse.in_single || parse.in_double
// 			|| !ft_isspace(line[*i])))
// 	{
// 		(void)data;
// 		if (chck_quote_state(line, i, &parse))
// 			continue ;
// 		handle_parse_token(line, i, &parse);
// 		if (handle_check_var(line, i, data, &parse))
// 			continue ;
// 		check_closing_quote(line, i, &parse);
// 		// if (*i > 0 && (line[*i] == '|' && ft_strncmp(line, "export", 6) != 0))
// 		// 	return (parse.buffer);
// 		// if (line[*i] == '<' && line[*i + 1] != '<')
// 		// {
// 		// 	append_char(&parse, line[*i]);
// 		// 	(*i)++;
// 		// 	return (parse.buffer);
// 		// }
// 		// if (chck_redir_pip(line, i))
// 		// 	continue ;
// 		(*i)++;
// 	}
// 	return (parse.buffer);
// }
