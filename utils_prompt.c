/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/20 22:16:48 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_hostname(void)
{
	int		fd;
	char	*hostname;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	hostname = get_next_line(fd);
	if (ft_strchr(hostname, '\n'))
		hostname[strlen(hostname) - 1] = '\0';
	close(fd);
	if (!hostname)
		hostname = "minishell";
	return (hostname);
}

static char	*ft_get_currentpath(void)
{
	char	*currentpath;
	char	*home;
	char	*result;

	currentpath = getcwd(NULL, 0);
	if (!currentpath)
		return (strdup("~"));
	home = getenv("HOME");
	if (home && strncmp(currentpath, home, strlen(home)) == 0)
	{
		result = (char *)malloc(strlen(currentpath) - strlen(home) + 2);
		if (!result)
		{
			free(currentpath);
			return (NULL);
		}
		result[0] = '~';
		strcpy(result + 1, currentpath + strlen(home));
		free(currentpath);
		return (result);
	}
	return (currentpath);
}

static char	*ft_get_username(void)
{
	char	*username;

	username = getenv("USER");
	if (!username)
		username = "minishell";
	username = ft_strjoin(username, "@");
	return (username);
}

void	get_promt(void)
{
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*tmp2;
	char	*current_path;

	username = ft_get_username();
	hostname = ft_get_hostname();
	tmp2 = ft_strjoin(username, hostname);
	prompt = ft_strdup(tmp2);
	current_path = ft_get_currentpath();
	printf("\e[1;32m");
	printf("%s", prompt);
	printf("\e[m");
	printf(":");
	printf("\e[1;34m");
	printf("%s", current_path);
	printf("\e[m");
	free(username);
	free(hostname);
	free(tmp2);
	free(prompt);
	free(current_path);
}
