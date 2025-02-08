/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:06:04 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/08 19:02:40 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipeline	*init_pipeline(void)
{
	t_pipeline	*pip;

	pip = ft_calloc(1, sizeof(t_pipeline));
	if (!pip)
		return (NULL);
	pip->cmds = NULL;
	return (pip);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->arg_cnt = 0;
	cmd->fd_in = -2;
	cmd->in_error = 0;
	cmd->input_file = NULL;
	cmd->fd_out = -2;
	cmd->out_error = 0;
	cmd->output_file = NULL;
	cmd->limiter = NULL;
	cmd->trunc = 0;
	cmd->append = 0;
	cmd->heredoc = 0;
	return (cmd);
}
