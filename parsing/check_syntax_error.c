/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:02:05 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/24 01:21:09 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_syntax_error(char *token)
{
	char	*msg;
	char	*tmp;

	if (!token)
		ft_print_error(NULL, NULL,
			"syntax error near unexpected token 'newline'");
	else
	{
		tmp = ft_strjoin("syntax error near unexpected token '", token);
		msg = ft_strjoin(tmp, "'");
		ft_print_error(NULL, NULL, msg);
		free(tmp);
		free(msg);
	}
	get_data(NULL)->exit_code = 2;
}

/* Verifie si `input[i]` est un cas d'erreur */
static int	is_syntax_error(char *input, int i, int expect_word, int prev_op)
{
	if (is_operator(input[i]) && expect_word)
		return (1);
	if ((input[i] == '>' || input[i] == '<') && input[i + 1] == '\0')
		return (1);
	if (input[i] == '|' && (i == 0 || prev_op)) // | en debut ou apres un autre operateur
		return (1);
	if (is_double_operator(input, i) && input[i] == '|' && (i == 0 || expect_word))
		return (1);
	return (0);
}

/* Recupere le token d'erreur a afficher */
static char	*get_error_token(char *input, int i)
{
	if (!input[i])
		return (ft_strdup("newline"));
	if (is_double_operator(input, i))
		return (ft_substr(input, i, 2));
	return (ft_substr(input, i, 1));
}

/* Verifie les erreurs de syntaxe dans `input` */
static char	*find_syntax_error(char *input)
{
	int		i;
	int		expecting_word;
	int		prev_operator;
	char	*error_token;

	i = 0;
	expecting_word = 0;
	prev_operator = 0;
	error_token = NULL;
	while (input[i])
	{
		if (is_syntax_error(input, i, expecting_word, prev_operator))
			return (get_error_token(input, i));
		prev_operator = is_operator(input[i]);
		expecting_word = is_operator(input[i]);
		if (is_double_operator(input, i))
			i += 2;
		else
			i++;
	}
	if (!error_token && expecting_word)
		error_token = ft_strdup("newline");
	return (error_token);
}

int	check_syntax_errors(char *input)
{
	char	*error_token;
	char	*tmp_input;
	int		ret;

	tmp_input = ft_trim_whitespace(input);
	if (!tmp_input)
		return (0);
	error_token = find_syntax_error(tmp_input);
	if (!error_token)
	{
		free(tmp_input);
		return (0);
	}
	print_syntax_error(error_token);
	free(error_token);
	ret = 1;
	free(tmp_input);
	return (ret);
}

// | echo hello
// 										| echo hello
//            | echo hello
// echo hello            |