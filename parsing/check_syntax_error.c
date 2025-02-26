/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:02:05 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 13:25:10 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_syntax_error(char *input, int i, int expect_word, int prev_op)
{
	if (is_operator(input[i]) && expect_word)
		return (1);
	if ((input[i] == '>' || input[i] == '<') && input[i + 1] == '\0')
		return (1);
	if (input[i] == '|' && (i == 0 || prev_op))
		return (1);
	if (input[i] == '|' && is_operator(input[i + 1]))
		return (1);
	if (input[i] == '|')
	{
		while (ft_isspace(input[i + 1]))
			i++;
		if (input[i + 1] == '|')
			return (1);
	}
	if (input[i] == '>')
	{
		if (input[i] == '>' && input[i + 1] == '>')
			i++;
		while (ft_isspace(input[i + 1]))
			i++;
		if (input[i + 1] == '>')
			return (1);
	}
	return (0);
}

static void	get_error_token(char *input, int i, char **error_token)
{
	if (!input[i])
	{
		*error_token = ft_strdup("newline");
		return ;
	}
	if (is_double_operator(input, i))
	{
		*error_token = ft_substr(input, i, 2);
		return ;
	}
	*error_token = ft_substr(input, i, 1);
	return ;
}

static void	check_double(int *i, char *input)
{
	if (is_double_operator(input, *i))
		(*i) += 2;
	else
		(*i)++;
}

static void	find_syntax_error(char *input, char **error_token)
{
	int		i;
	int		expecting_word;
	int		prev_operator;
	int		in_single;
	int		in_double;

	i = 0;
	expecting_word = 0;
	prev_operator = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		update_quote_state(input, &in_single, &in_double, i);
		if (!in_single && !in_double)
		{
			if (is_syntax_error(input, i, expecting_word, prev_operator))
				return (get_error_token(input, i, error_token));
			prev_operator = is_operator(input[i]);
			expecting_word = is_operator(input[i]);
		}
		check_double(&i, input);
	}
	if (!error_token && expecting_word)
		*error_token = ft_strdup("newline");
}

int	check_syntax_errors(char *input)
{
	char	*error_token;
	char	*tmp_input;
	int		ret;

	error_token = NULL;
	tmp_input = ft_trim_whitespace(input);
	if (!tmp_input)
		return (0);
	find_syntax_error(tmp_input, &error_token);
	if (!error_token)
	{
		free(tmp_input);
		return (0);
	}
	if (!error_token)
		ft_print_error(NULL, NULL,
			"syntax error near unexpected token 'newline'");
	else
		ft_print_error(NULL, NULL, "syntax error near unexpected token");
	get_data(NULL)->exit_code = 2;
	free(error_token);
	ret = 1;
	free(tmp_input);
	return (ret);
}
