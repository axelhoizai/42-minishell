/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:54:30 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/23 03:00:08 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_space(char **new_input, char *input, int *i)
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

static char *extract_word(char *input, int *i, int *in_single, int *in_double)
{
	int		j;
	char	*word;

	j = *i;
	while (input[j] && !ft_isspace(input[j]))
	{
		update_quote_state(input, in_single, in_double, j);
		j++;
	}
	word = ft_substr(input, *i, j - *i);
	*i = j;
	return (word);
}


// static void	append_expanded_word(char **new_input, char **word, int in_single, int in_double)
void	ap_exp_word(char **new_str, char **word, int in_single, int in_double)
{
	char	*temp;
	char	*tmp_new;

	if (ft_strchr(*word, '*') && in_single == 0 && in_double == 0)
		expand_wildcard(word);
	temp = ft_strjoin(*new_str, " ");
	tmp_new = *new_str;
	*new_str = ft_strjoin(temp, *word);
	free(temp);
	free(tmp_new);
	free(*word);
}

void	check_and_expand_wildcard(char **input)
{
	int		in_single = 0;
	int		in_double = 0;
	int		i = 0;
	char	*new_input;
	char	*word;

	new_input = ft_strdup("");
	if (!new_input)
		return;
	while ((*input)[i])
	{
		while ((*input)[i] && ft_isspace((*input)[i]))
			append_space(&new_input, *input, &i);
		word = extract_word(*input, &i, &in_single, &in_double);
		if (!word)
			return;
        ap_exp_word(&new_input, &word, in_single, in_double);
	}
	free(*input);
	*input = new_input;
}
