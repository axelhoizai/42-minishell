/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:59:50 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 13:45:23 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_process_id(void)
{
	int		fd;
	char	buffer[32];
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buffer, 31) <= 0)
	{
		close(fd);
		return (-1);
	}
	buffer[31] = '\0';
	pid = ft_atoi(buffer);
	close(fd);
	return (pid);
}

char	*extract_uid(char *buffer)
{
	char	*uid_start;
	char	*uid;
	int		i;

	uid_start = strstr(buffer, "Uid:");
	if (!uid_start)
		return (NULL);
	uid_start += 4;
	while (*uid_start == ' ' || *uid_start == '\t')
		uid_start++;
	uid = malloc(11);
	if (!uid)
		return (NULL);
	i = 0;
	while (i < 10 && uid_start[i] >= '0' && uid_start[i] <= '9')
	{
		uid[i] = uid_start[i];
		i++;
	}
	uid[i] = '\0';
	return (uid);
}

char	*get_uid(void)
{
	int		fd;
	int		bytes_read;
	char	buffer[1024];

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (extract_uid(buffer));
}

t_data	*get_data(t_data *new_data)
{
	static t_data	*data = NULL;

	if (new_data)
		data = new_data;
	return (data);
}

