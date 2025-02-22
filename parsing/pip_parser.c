/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:40:08 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/22 17:25:08 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirection(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (1);
	if (ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	if (ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

static t_command	*parse_command(char **tokens, int *i, t_data *data)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
	{
		if (is_redirection(tokens[*i]))
		{
			handle_redirec(tokens, i, cmd, data);
		}
		else
		{
			cmd->args = add_to_tab(cmd->args, tokens[*i]);
			cmd->arg_cnt += 1;
		}
		fflush(stdout);
		(*i)++;
	}
	return (cmd);
}

t_pipeline	*parse_pipeline(char **tokens, t_data *data)
{
	t_pipeline	*pipeline;
	t_command	*cmd;
	int			i;

	pipeline = init_pipeline();
	if (!pipeline)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		cmd = parse_command(tokens, &i, data);
		if (!cmd)
		{
			free_pipeline(pipeline);
			pipeline = NULL;
			break ;
		}
		add_command_to_pipeline(pipeline, cmd);
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
		{
			pipeline->pipe_cnt++;
			i++;
		}
	}
	return (pipeline);
}

void	init_pipe_start(t_pipeline *pip)
{
	int	i;

	i = pip->pipe_cnt;
	while (i >= 0)
	{
		if (pip->cmds[i]->limiters)
		{
			pip->start = i;
			break ;
		}
		i--;
	}
}

void	print_pipeline(t_pipeline *pipeline)
{
	int			i;
	int			j;
	t_command	*cmd;

	// (void)pipeline;
	if (!pipeline)
		return ;
	i = 0;
	while (pipeline->cmds && pipeline->cmds[i])
	{
		cmd = pipeline->cmds[i];
		printf("[%d] : Command %d:\n", i, i + 1);
		if (cmd->args)
		{
			j = 0;
			printf("[%d] : Arguments: ", i);
			while (cmd->args[j])
				printf("'%s' ", cmd->args[j++]);
			printf("\n");
			printf("arg_cnt : %d\n", cmd->arg_cnt);
		}
		if (cmd->input_file)
			printf("[%d] : Input file: %s\n", i, cmd->input_file);
		if (cmd->output_file)
			printf("[%d] : Out: %s (append: %d)\n", i, cmd->output_file, cmd->append);
		if (cmd->heredoc)
			printf("[%d] : Heredoc: enabled\n", i);
		if (cmd->heredoc)
		{
			j = 0;
			while (cmd->limiters && cmd->limiters[j])
			{
				printf("[%d] : limiter[%d]: %s\n", i, j, cmd->limiters[j]);
				j++;
			}
		}
		i++;
	}
	pipeline->cmd_count = i;
	printf("pipe count : [%d]\n", pipeline->pipe_cnt);
	printf("cmd count  : [%d]\n", pipeline->cmd_count);
}
