/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:40:29 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/12 00:16:56 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? Build cmds like "cat -e"
char	**add_to_tab(char **tab, const char *arg)
{
	char	**new_tab;
	int		size;
	int		i;

	size = 0;
	while (tab && tab[size])
		size++;
	new_tab = ft_calloc(size + 2, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(arg);
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}

//? reBuild the input with tokenization
void	add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd)
{
	t_command	**new_cmds;
	int			size;
	int			i;

	size = 0;
	while (pipeline->cmds && pipeline->cmds[size])
		size++;
	new_cmds = ft_calloc(size + 2, sizeof(t_command *));
	if (!new_cmds)
		return ;
	i = 0;
	while (pipeline->cmds && pipeline->cmds[i])
	{
		new_cmds[i] = pipeline->cmds[i];
		i++;
	}
	new_cmds[i] = cmd;
	new_cmds[i + 1] = NULL;
	free(pipeline->cmds);
	pipeline->cmds = new_cmds;
}
