/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_expand_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 22:55:15 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/26 13:24:52 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_whitespace(char **new_input, char *input, int *i)
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

static void	append_expanded_word(char **new_input, char **word)
{
	char	*tmp_new;

	tmp_new = *new_input;
	*new_input = ft_strjoin(*new_input, *word);
	free(tmp_new);
	free(*word);
}

void	check_and_expand_operators(char **input)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*new_input;
	char	*word;

	i = 0;
	in_single = 0;
	in_double = 0;
	new_input = ft_strdup("");
	if (!new_input)
		return ;
	while ((*input)[i])
	{
		while ((*input)[i] && ft_isspace((*input)[i]))
			append_whitespace(&new_input, *input, &i);
		word = extract_word(*input, &i, &in_single, &in_double);
		if (!word)
			break ;
		if (!in_single && !in_double)
			format_operators_and_redirections(&word);
		append_expanded_word(&new_input, &word);
	}
	free(*input);
	*input = new_input;
}
