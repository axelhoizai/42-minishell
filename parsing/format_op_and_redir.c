/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 22:56:44 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_operator(char **new_input, char *input, int *i)
{
	char	*temp;
	char	*tmp_new;

	if ((input[*i] == '>' && input[*i + 1] == '|') ||
		(input[*i] == '<' && input[*i + 1] == '|'))
	{
		temp = ft_substr(input, *i, 2);
		*i += 2;
	}
	else if (is_double_operator(input, *i))
	{
		temp = ft_substr(input, *i, 2);
		*i += 2;
	}
	else
	{
		temp = ft_substr(input, *i, 1);
		*i += 1;
	}
	tmp_new = *new_input;
	*new_input = ft_strjoin(*new_input, temp);
	free(temp);
	free(tmp_new);
}

static void	append_char_or_space(char **new_input, char *input, int *i)
{
	char	*temp;
	char	*tmp_new;

	temp = ft_substr(input, *i, 1);
	tmp_new = *new_input;
	*new_input = ft_strjoin(*new_input, temp);
	free(temp);
	free(tmp_new);
	(*i)++;
}

static void	handle_operator_spacing(char **new_input, char *input, int *i)
{
	char	*tmp_new;

	if (*i > 0 && !ft_isspace(input[*i - 1]))
	{
		tmp_new = *new_input;
		*new_input = ft_strjoin(*new_input, " ");
		free(tmp_new);
	}
	append_operator(new_input, input, i);
	if (input[*i] && !ft_isspace(input[*i]))
	{
		tmp_new = *new_input;
		*new_input = ft_strjoin(*new_input, " ");
		free(tmp_new);
	}
}

static void	process_input_chars(char **new_input, char *input, int *i,
								int *in_single, int *in_double)
{
	update_quote_state(input, in_single, in_double, *i);
	if (!(*in_single) && !(*in_double) && is_operator(input[*i]))
		handle_operator_spacing(new_input, input, i);
	else
		append_char_or_space(new_input, input, i);
}

void	format_operators_and_redirections(char **input)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*new_input;

	i = 0;
	in_single = 0;
	in_double = 0;
	new_input = ft_strdup("");
	if (!new_input)
		return ;
	while ((*input)[i])
		process_input_chars(&new_input, *input, &i, &in_single, &in_double);
	free(*input);
	*input = new_input;
}

//<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action echo > >> < * ? [ ] | ; [ ] || && ( ) & # $ >| <| <<
//<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ >| <| <<"
// <<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ >| <| <<'