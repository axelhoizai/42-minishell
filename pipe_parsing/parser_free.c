/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:07:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 19:31:07 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	free(cmd);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	if (pipeline->commands)
	{
		i = 0;
		while (pipeline->commands[i])
		{
			free_command(pipeline->commands[i]);
			i++;
		}
		free(pipeline->commands);
	}
	free(pipeline);
}
