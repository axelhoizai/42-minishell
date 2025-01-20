/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:00:43 by mdemare           #+#    #+#             */
/*   Updated: 2024/10/29 16:22:51 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (count);
}

static char	**ft_allocate_split(char const *s, char c)
{
	char	**split;

	split = (char **)malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (split);
}

static void	ft_free_split_fail(char **split, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

static int	ft_fill_split(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		start;

	i = 0;
	j = 0;
	start = -1;
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		if ((s[i + 1] == '\0' || s[i] == c) && start != -1)
		{
			if (s[i] == c)
				split[j] = ft_substr(s, start, i - start);
			else
				split[j] = ft_substr(s, start, i - start + 1);
			if (!split[j++])
				return (ft_free_split_fail(split, j - 1), 0);
			start = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = ft_allocate_split(s, c);
	if (!split)
		return (NULL);
	if (!ft_fill_split(split, s, c))
		return (NULL);
	return (split);
}
/* int	main(void)
{
	char	**result;
	char	str[] = "hello,world,this,is,a,test";
	int		i;

	result = ft_split(str, ',');
	if (!result)
		printf("Memory allocation failed.\n");
	i = 0;
	while (result[i])
	{
		printf("Word %d: %s\n", i + 1, result[i]);
		i++;
	}
	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
	return (0);
} 
// cc -g -Wall -Wextra -Werror ft_split.c ft_substr.c ft_strdup.c ft_strlen.c
*/
