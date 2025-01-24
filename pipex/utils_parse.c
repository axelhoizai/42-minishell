/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:04:52 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 19:58:25 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_quote(const char *str, char quote)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != quote)
		count++;
	if (str[count] == quote)
		return (count + 1);
	return (-1);
}

static int	count_words(const char *str)
{
	int	count = 0;
	int	words = 0;
	int	len;

	while (str[count])
	{
		while (str[count] == ' ' || str[count] == '\t')
			count++;
		if (str[count] == '\'' || str[count] == '"')
		{
			len = handle_quote(&str[count + 1], str[count]);
			if (len == -1)
				return (-1);
			count += len + 1;
			words++;
		}
		else if (str[count])
		{
			while (str[count] && !(str[count] == ' ' || str[count] == '\t'
					|| str[count] == '\'' || str[count] == '"'))
				count++;
			words++;
		}
	}
	return (words);
}

static void	handle_quoted_word(const char *str, char **result, int *i, int *j)
{
	char	quote;
	int		start;
	int		len;

	quote = str[*i];
	start = *i + 1;
	len = handle_quote(&str[*i + 1], quote);
	if (len == -1)
		return ;
	result[*j] = malloc(sizeof(char) * len);
	if (!result[*j])
		return ;
	ft_memcpy(result[*j], &str[start], len - 1);
	result[*j][len - 1] = '\0';
	*i += len + 1;
	(*j)++;
}

static void	handle_unquoted_word(const char *str, char **result, int *i, int *j)
{
	int	start;
	int	len;

	start = *i;
	while (str[*i] && !(str[*i] == ' ' || str[*i] == '\t'
			|| str[*i] == '\'' || str[*i] == '"'))
		(*i)++;
	len = *i - start;
	result[*j] = malloc(sizeof(char) * (len + 1));
	if (!result[*j])
		return ;
	ft_memcpy(result[*j], &str[start], len);
	result[*j][len] = '\0';
	(*j)++;
}

char	**utils_parse_args(const char *str)
{
	char	**result;
	int		count;
	int		i = 0;
	int		j = 0;
	char	*tmp;
	int		end_quote = 0;

	if (!str)
		return (NULL);
	count = count_words(str);
	if (count == -1)
		return (NULL);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			handle_quoted_word(str, result, &i, &j);
			end_quote = 1;
			tmp = ft_strdup(result[j - 1]);
			free(result[j - 1]);
			
		}
		else if (str[i])
		{
			if (end_quote == 1)
			{
				end_quote = 0;
				handle_unquoted_word(str, result, &i, &j);
				tmp = ft_strjoin(tmp, result[j - 1]);
				free(result[j - 1]);
				result[j - 2] = ft_strdup(tmp);
				free(tmp);
				j -=1;
			}
			else
				handle_unquoted_word(str, result, &i, &j);
		}
	}
	result[j] = NULL;
	return (result);
}
