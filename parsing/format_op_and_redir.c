/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_op_and_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:46:56 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/24 17:56:11 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_operator(char **new_input, char *input, int *i)
{
	int		start;
	char	*operator;
	char	*tmp_new;

	start = *i;
	if ((input[*i] == '>' && input[*i + 1] == '|') ||
		(input[*i] == '<' && input[*i + 1] == '|'))
		*i += 2;
	else
		while (input[*i] && input[*i] == input[start])
			(*i)++;
	operator = ft_substr(input, start, *i - start);
	tmp_new = *new_input;
	*new_input = ft_strjoin(tmp_new, operator);
	free(operator);
	free(tmp_new);
}

static void	append_char_or_space(char **new_input, char *input, int *i)
{
	char	*temp;
	char	*tmp_new;

	temp = ft_substr(input, *i, 1);
	tmp_new = *new_input;
	*new_input = ft_strjoin(tmp_new, temp);
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
		*new_input = ft_strjoin(tmp_new, " ");
		free(tmp_new);
	}
	append_operator(new_input, input, i);
	if (input[*i] && !ft_isspace(input[*i]))
	{
		tmp_new = *new_input;
		*new_input = ft_strjoin(tmp_new, " ");
		free(tmp_new);
	}
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
	{
			update_quote_state(*input, &in_single, &in_double, i);
			if (in_single == 0 && in_double == 0 && is_operator((*input)[i]))
				handle_operator_spacing(&new_input, *input, &i);
			else
				append_char_or_space(&new_input, *input, &i);
	}
	free(*input);
	*input = new_input;
}

//<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne| echo > >> < * ? [ ] | ; [ ] || && ( ) & # $ >| <| <<
//<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne| echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ >| <| <<"
//<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne| echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ >| <| <<'
//<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne|
//"<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne|"
//'<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne|'

//'<<ceci<est|un||test>|pour<|voir>le*>>parsing>>>actuel&&en&action>>>>>>>>>>si<<<<<<<<<<<il||||||||||||||fonctionne|'
//echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" | cat -e