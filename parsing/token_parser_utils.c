/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:21:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/24 12:34:09 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Vérifie si le caractère est un opérateur simple */
int	is_operator(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

/* Vérifie si deux caractères forment un opérateur double (ex: '||', '&&', '>>', '<<') */
int	is_double_operator(const char *input, int i)
{
	if (!input[i] || !input[i + 1])
		return (0);
	if ((input[i] == '|' && input[i + 1] == '|')
		|| (input[i] == '&' && input[i + 1] == '&')
		|| (input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>'))
		return (1);
	return (0);
}
