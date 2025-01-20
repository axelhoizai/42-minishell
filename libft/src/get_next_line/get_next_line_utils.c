/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:10:27 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/08 10:37:20 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	unsigned char	*ptr;
// 	size_t			total_size;
// 	size_t			i;

// 	i = 0;
// 	if (size == 0 || nmemb == 0)
// 		return (malloc(0));
// 	total_size = nmemb * size;
// 	if (total_size / nmemb != size)
// 		return (NULL);
// 	ptr = malloc(total_size);
// 	if (!ptr)
// 		return (NULL);
// 	while (i < total_size)
// 		ptr[i++] = '\0';
// 	return (ptr);
// }

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	joined = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s != '\0')
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

char	*ft_strdup_gnl(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)ft_calloc(len + 2, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		dup[i++] = '\n';
	dup[i] = '\0';
	return (dup);
}
