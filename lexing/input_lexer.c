/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:18:58 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 03:02:26 by kalicem          ###   ########.fr       */
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

void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

bool	lexing_string(char *str, char **lexingv, int *count, t_data *data)
{
	int		i;
	char	*token;

	i = 0;
	while (str && str[i])
	{
		skip_whitespace(str, &i);
		if (str[i])
		{
			// if (!token)
			token = parse_lexer(str, &i, data);
			if (!token)
				return (free_tab(lexingv), false);
			// if (!ft_isspace(token[0]) && ft_strlen(token) > 0)
			lexingv[(*count)++] = token;
			// else if (token)
			// 	free(token);
			// if (!token)
			// 	token = skip_pips(str, &i);
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

	if (!input || check_unclosed_quotes(input))
		return (ft_print_error(NULL, NULL, "Error: unclosed quotes"), NULL);
	lexingv = malloc(sizeof(char *) * 256);
	if (!lexingv)
		return (NULL);
	count = 0;
	if (!lexing_string(input, lexingv, &count, data))
		return (NULL);
	print_tab_lexing(lexingv);
	return (lexingv);
}

//? Get the input and lexing
void	input_lexer(char *input, t_data *data)
{
	char	**lexingv;
	int		lexingc;
	
	if (!input)
		return ;
	check_and_expand_wildcard(&input);
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
	////////////////////////////////////////////
	// parse_argv(lexingv, lexingc, data); //a revoir
	if (lexingc > 0)
	{
		send_to_exec(lexingv, data);
		return ;
	}
}
