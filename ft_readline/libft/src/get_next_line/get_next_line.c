/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:04:45 by mdemare           #+#    #+#             */
/*   Updated: 2024/11/03 17:07:18 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*extract_line(char *save)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!save || !*save)
		return (NULL);
	len = 0;
	while (save[len] && save[len] != '\n')
		len++;
	line = ft_strdup_gnl(save, len);
	if (!line)
		return (NULL);
	i = 0;
	if (save[len] == '\n')
		len++;
	while (save[len + i])
	{
		save[i] = save[len + i];
		i++;
	}
	save[i] = '\0';
	return (line);
}

static char	*read_and_store(int fd, char *buffer)
{
	char	*read_buffer;
	char	*temp;
	ssize_t	bytes_read;

	read_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buffer), free(buffer), NULL);
		read_buffer[bytes_read] = '\0';
		temp = ft_strjoin_gnl(buffer, read_buffer);
		if (!temp)
			return (free(read_buffer), free(buffer), NULL);
		free(buffer);
		buffer = temp;
	}
	free(read_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*buffer[FD_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = (char *)ft_calloc(1, sizeof(char));
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = read_and_store(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	next_line = extract_line(buffer[fd]);
	if (!next_line || *next_line == '\0')
		return (free(next_line), free(buffer[fd]), buffer[fd] = NULL, NULL);
	if (*buffer[fd] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (next_line);
}

// int	main(void)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*next_line_fd1;
// 	char	*next_line_fd2;
// 	int		count;

// 	count = 0;
// 	fd = open("1char.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	if (fd2 < 0)
// 		return (1);
// 	next_line_fd1 = get_next_line(fd);
// 	next_line_fd2 = get_next_line(fd2);
// 	while (next_line_fd1 || next_line_fd2)
// 	{
// 		if (next_line_fd1)
// 		{
// 			count++;
// 			printf("[%d] (fd1): %s", count, next_line_fd1);
// 			free(next_line_fd1);
// 			next_line_fd1 = get_next_line(fd);
// 		}
// 		if (next_line_fd2)
// 		{
// 			count++;
// 			printf("[%d] (fd2): %s", count, next_line_fd2);
// 			free(next_line_fd2);
// 			next_line_fd2 = get_next_line(fd2);
// 		}
// 	}
// 	close(fd);
// 	close(fd2);
// 	return (0);
// }
