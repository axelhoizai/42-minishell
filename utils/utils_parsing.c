/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:13:26 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 20:55:13 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_argv(char **argv)
{
	int		i;
	char	*cmd;
	char	*tmp;

	if (!argv || !argv[0])
		return (NULL);
	cmd = ft_strdup(argv[0]);
	if (!cmd)
		return (NULL);
	i = 1;
	while (argv[i])
	{
		tmp = ft_strjoin(cmd, " ");
		free(cmd);
		if (!tmp)
			return (NULL);
		cmd = ft_strjoin(tmp, argv[i]);
		free(tmp);
		if (!cmd)
			return (NULL);
		i++;
	}
	return (cmd);
}
