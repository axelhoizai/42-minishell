/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:18:29 by ahoizai           #+#    #+#             */
/*   Updated: 2025/02/24 17:06:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_input(char **tokens, int *i, t_command *cmd, t_data *data)
{
	cmd->heredoc = 0;
	if (cmd->input_file || cmd->in_error == 1)
	{
		if (cmd->fd_in > -1)
			close(cmd->fd_in);
		free(cmd->input_file);
	}
	cmd->input_file = ft_strdup(tokens[++(*i)]);
	cmd->fd_in = open_file(cmd, cmd->input_file, 1);
	if (cmd->fd_in == -1 || cmd->in_error == 1)
	{
		if (cmd->fd_in == -1)
		{
			if (cmd->in_error == 0 && cmd->out_error == 0)
				ft_print_error(NULL, cmd->input_file,
					"No such file or directory"); //dois resortir exit 2 en fonction des cas??
			cmd->in_error = 1;
		}
		else
		{
			close(cmd->fd_in);
			cmd->fd_in = -1;
		}
		data->exit_code = EXIT_FAILURE;
	}
}

static void	handle_fd_error(t_command *cmd, t_data *data)
{
	if (cmd->in_error == 0)
	{
		if (cmd->out_error == 0 && cmd->in_error == 0)
			ft_print_error(NULL, cmd->output_file, "No such file or directory");
		cmd->fd_out = -1;
	}
	if (cmd->fd_in > -1)
		close(cmd->fd_in);
	cmd->out_error = 1;
	data->exit_code = EXIT_FAILURE;
}

static void	handle_output(char **tokens, int *i, t_command *cmd, t_data *data)
{
	if (cmd->fd_out > -1 || cmd->output_file)
	{
		if (cmd->fd_out > -1)
			close(cmd->fd_out);
		free(cmd->output_file);
	}
	cmd->output_file = ft_strdup(tokens[++(*i)]);
	if (cmd->out_error == 0)
	{
		if (cmd->trunc == 1)
			cmd->fd_out = open_outfile(cmd, cmd->output_file, data, 0);
		else if (cmd->append == 1)
			cmd->fd_out = open_outfile(cmd, cmd->output_file, data, 1);
		cmd->trunc = 0;
		cmd->append = 0;
	}
	if (cmd->fd_out == -1 && cmd->out_error == 0)
		handle_fd_error(cmd, data);
	if (cmd->in_error == 1)
	{
		if (cmd->fd_out > -1)
			close(cmd->fd_out);
	}
}

void	handle_redirec(char **tokens, int *i, t_command *cmd, t_data *data)
{
	if (ft_strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
		handle_input(tokens, i, cmd, data);
	else if (ft_strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
	{
		cmd->trunc = 1;
		handle_output(tokens, i, cmd, data);
	}
	else if (ft_strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
	{
		cmd->append = 1;
		handle_output(tokens, i, cmd, data);
	}
	else if (ft_strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
	{
		cmd->limiters = add_to_tab(cmd->limiters, tokens[++(*i)]);
		cmd->heredoc = 1;
	}
}
