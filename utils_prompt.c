/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/21 13:33:25 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_hostname(void)
{
	int		fd;
	char	*hostname;
	char	*tmp;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return ("minishell");
	tmp = get_next_line(fd);
	if (ft_strchr(tmp, '\n'))
		tmp[strlen(tmp) - 1] = '\0';
	close(fd);
	hostname = ft_strtok(tmp, ".");
	if (!hostname)
		hostname = "minishell";
	ft_strtok(NULL, ".");
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

char	*color_prompt(char *prompt, char *current_path)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*color_prompt;
	char	*colorcurrentpath;

	tmp1 = ft_strjoin("\e[1;32m", prompt);
	tmp2 = ft_strjoin(tmp1, "\e[m");
	free(tmp1);
	tmp3 = ft_strjoin(tmp2, ":");
	free(tmp2);
	
	tmp1 = ft_strjoin("\e[1;34m", current_path);
	tmp2 = ft_strjoin(tmp1, "\e[m");
	colorcurrentpath = ft_strjoin(tmp2, "$ ");
	free(tmp1);
	free(tmp2);
	color_prompt = ft_strjoin(tmp3, colorcurrentpath);
	free(tmp3);
	free(colorcurrentpath);
	return (color_prompt);
}

//PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
char	*get_promt(void)
{
	char	*username;
	char	*hostname;
	char	*prompt;
	char	*tmp2;
	char	*current_path;
	

	username = ft_get_username();
	hostname = ft_get_hostname();
	tmp2 = ft_strjoin(username, hostname);
	current_path = ft_get_currentpath();
	prompt = color_prompt(tmp2, current_path);
	free(tmp2);
	free(username);
	if (ft_strncmp(hostname, "minishell", 9) != 0)
		free(hostname);
	free(current_path);
	return (prompt);
}
