/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:04:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 19:24:37 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_quote(const char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

static int	count_words(const char *str)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] != '\0')
			word_count++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			i += handle_quote(&str[i], str[i - 1]);
		}
		else
		{
			while (str[i] && !(str[i] == ' '
					|| str[i] == '\t' || str[i] == '\n')
				&& str[i] != '\'' && str[i] != '\"')
				i++;
		}
	}
	return (word_count);
}

static void	handle_quoted_word(const char *str, char **result, int *i, int *j)
{
	char	quote;
	int		start;
	int		len;
	int		k;

	k = 0;
	quote = str[*i];
	start = *i + 1;
	(*i)++;
	len = handle_quote(&str[*i], quote);
	result[*j] = (char *)malloc(sizeof(char) * len + 1);
	if (result[*j])
	{
		while (k < len - 1)
		{
			result[*j][k] = str[start + k];
			k++;
		}
		result[*j][k] = '\0';
	}
	(*i) += len;
	(*j)++;
}

static void	handle_unquoted_word(const char *str, char **result, int *i, int *j)
{
	int	start;
	int	len;
	int	k;

	k = 0;
	start = *i;
	while (str[*i] && !(str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
		&& str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	len = *i - start;
	result[*j] = (char *)malloc(sizeof(char) * (len + 1));
	if (result[*j])
	{
		while (k < len)
		{
			result[*j][k] = str[start + k];
			k++;
		}
		result[*j][k] = '\0';
	}
	(*j)++;
}

char	**utils_parse_args(const char *str)
{
	char	**result;
	int		i;
	int		j;

	if (str == NULL)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(str) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if ((str[i] == '\'' || str[i] == '\"'))
			handle_quoted_word(str, result, &i, &j);
		else if (str[i] != '\0')
			handle_unquoted_word(str, result, &i, &j);
	}
	result[j] = NULL;
	return (result);
}
