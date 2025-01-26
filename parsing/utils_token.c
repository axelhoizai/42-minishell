/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 02:50:38 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/26 18:57:25 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unclosed_quotes(const char *line)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (line[i] == '"' && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

void	init_parse(t_parse *parse, int size)
{
	parse->buffer = malloc(size);
	if (!parse->buffer)
		exit(1);
	parse->len = 0;
	parse->capacity = size;
	parse->buffer[0] = '\0';
}

void	append_char(t_parse *parse, char c)
{
	if (parse->len + 1 < parse->capacity)
	{
		parse->buffer[parse->len++] = c;
		parse->buffer[parse->len] = '\0';
	}
	else
		exit(1);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
