/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:02:05 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/26 16:57:23 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_double_check(char *input, int i)
{
	if (input[i] == '<')
	{
		if (input[i] == '<' && input[i + 1] == '<')
			i++;
		while (ft_isspace(input[i + 1]))
			i++;
		if (input[i + 1] == '<' )
			return (1);
	}
	if (input[i] == '>')
	{
		if (input[i] == '>' && input[i + 1] == '>')
			i++;
		while (ft_isspace(input[i + 1]))
			i++;
		if (input[i] == '>' || input[i + 1] == '>' )
			return (1);
	}
	return (0);
}

int	is_syntax_error(char *input, int i, int expect_word, int prev_op)
{
	if (is_operator(input[i]) && expect_word)
		return (1);
	if (input[i] == '<' && input[i + 1] == '<' && !input[i + 2])
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
		if (input[i + 1] == '|' || is_operator(input[i + 1]))
			return (1);
	}
	if (is_double_check(input, i) == 1)
		return (1);
	return (0);
}
