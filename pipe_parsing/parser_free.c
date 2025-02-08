/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:07:48 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/08 19:00:08 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	free_command(t_command *cmd)
// {
// 	int	i;

// 	if (!cmd)
// 		return ;
// 	if (cmd->args)
// 	{
// 		i = 0;
// 		while (cmd->args[i])
// 		{
// 			free(cmd->args[i]);
// 			i++;
// 		}
// 		free(cmd->args);
// 	}
// 	if (cmd->input_file)
// 		free(cmd->input_file);
// 	if (cmd->fd_in > -1)
// 		close(cmd->fd_in);
// 	if (cmd->output_file)
// 		free(cmd->output_file);
// 	if (cmd->limiter)
// 		free(cmd->limiter);
// 	free(cmd);
// }

// void	free_pipeline(t_pipeline *pipeline)
// {
// 	int	i;

// 	if (!pipeline)
// 		return ;
// 	if (pipeline->cmds)
// 	{
// 		i = 0;
// 		while (pipeline->cmds[i])
// 		{
// 			free_command(pipeline->cmds[i]);
// 			i++;
// 		}
// 		free(pipeline->cmds);
// 	}
// 	free(pipeline);
// }

void free_command(t_command *cmd)
{
    int i;

    if (!cmd)
        return;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
            free(cmd->args[i++]);
        free(cmd->args);
        cmd->args = NULL;
    }
    if (cmd->input_file)
    {
        free(cmd->input_file);
        cmd->input_file = NULL;
    }
    if (cmd->output_file)
    {
        free(cmd->output_file);
        cmd->output_file = NULL;
    }
    if (cmd->limiter)
    {
        free(cmd->limiter);
        cmd->limiter = NULL;
    }
    if (cmd->fd_in > -1)
    {
        close(cmd->fd_in);
        cmd->fd_in = -1;
    }
    if (cmd->fd_out > -1)
    {
        close(cmd->fd_out);
        cmd->fd_out = -1;
    }
    free(cmd);
    cmd = NULL;
}

void free_pipeline(t_pipeline *pipeline)
{
    int i;

    if (!pipeline)
        return;
    i = 0;
    while (i < pipeline->cmd_count)
        if (pipeline->cmds[i])
            free_command(pipeline->cmds[i++]);
    free(pipeline->cmds);
    pipeline->cmds = NULL;
    free(pipeline);
    pipeline = NULL;
}
