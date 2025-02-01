/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:40:29 by kalicem           #+#    #+#             */
/*   Updated: 2025/01/31 17:59:02 by ahoizai          ###   ########.fr       */
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
	t_command	**new_commands;
	int			size;
	int			i;

	size = 0;
	while (pipeline->commands && pipeline->commands[size])
		size++;
	new_commands = ft_calloc(size + 2, sizeof(t_command *));
	if (!new_commands)
		return ;
	i = 0;
	while (pipeline->commands && pipeline->commands[i])
	{
		new_commands[i] = pipeline->commands[i];
		i++;
	}
	new_commands[i] = cmd;
	new_commands[i + 1] = NULL;
	free(pipeline->commands);
	pipeline->commands = new_commands;
}
