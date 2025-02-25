/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/25 13:53:43 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab_lexing(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("lexing [%d] : \'%s\'\n", i, tab[i]);
		i++;
	}
}

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
			// if (ft_strlen(token) > 0)
			lexingv[(*count)++] = token;
			// else if (token)
			// 	free(token);
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

//? Get the input and lexing
void	input_lexer(char *input, t_data *data)
{
	char	**lexingv;
	int		lexingc;

	if (!input || ft_strlen(input) == 0)
		return ;
	if (check_unclosed_quotes(input))
		return (ft_print_error(NULL, NULL, "Error: unclosed quotes"));
	check_and_expand_wildcard(&input);
	// printf("input check_and_expand_wildcard = %s\n", input);
	format_operators_and_redirections(&input);
	// printf("input format_operators_and_redirections = %s\n", input);
	if (check_syntax_errors(input))
	{
		data->exit_code = 2;
		free(input);
		return ;
	}
	lexingv = NULL;
	lexingc = 0;
	lexingv = lexer_args(input, data);
	free(input);
	if (lexingv && !lexingv[0])
	{
		free(lexingv);
		data->exit_code = 0;
		return ;
	}
	while (lexingv && lexingv[lexingc])
		lexingc++;
	print_tab_lexing(lexingv);
	if (lexingc > 0)
		return (send_to_exec(lexingv, data));
	free_tab(lexingv);
}
