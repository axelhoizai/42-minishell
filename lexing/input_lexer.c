/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/27 13:46:46 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	lexing_string(char *str, char **lexingv, int *count, t_data *data)
{
	int		i;
	char	*token;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
		{
			token = parse_lexer(str, &i, data);
			if (!token)
				return (free_tab(lexingv), false);
			lexingv[(*count)++] = token;
		}
	}
	lexingv[*count] = NULL;
	if (*count == 0)
		return (free_tab(lexingv), false);
	return (true);
}

char	**lexer_args(char *input, t_data *data)
{
	char	**lexingv;
	int		count;
	int		open_parens;

	open_parens = 0;
	if (!input || check_unclosed_quotes(input))
		return (ft_print_error(NULL, NULL, "Error: unclosed quotes"), NULL);
	lexingv = ft_calloc(256, sizeof(char *));
	if (!lexingv)
		return (NULL);
	count = 0;
	if (!lexing_string(input, lexingv, &count, data))
	{
		if (count == 0)
			lexingv = NULL;
		if (lexingv)
			free_tab(lexingv);
		return (NULL);
	}
	return (lexingv);
}

void	free_lexer(void *var, int exit_code)
{
	free(var);
	get_data(NULL)->exit_code = exit_code;
}

void	input_lexer(char *input, t_data *data)
{
	char	**lexingv;
	int		lexingc;
	char	*error_token;

	error_token = NULL;
	if (!input || ft_strlen(input) == 0)
		return ;
	if (check_unclosed_quotes(input))
		return (ft_print_error(NULL, NULL, "Error: unclosed quotes"));
	check_and_expand_wildcard(&input);
	format_operators_and_redirections(&input);
	if (check_syntax_errors(input))
		return (free_lexer(input, 2));
	lexingv = NULL;
	lexingc = 0;
	lexingv = lexer_args(input, data);
	free(input);
	if (lexingv && !lexingv[0])
		return (free_lexer(lexingv, 0));
	while (lexingv && lexingv[lexingc])
		lexingc++;
	if (lexingc > 0)
		return (send_to_exec(lexingv, data));
	free_tab(lexingv);
}
