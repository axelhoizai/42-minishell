/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:40:08 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/27 11:05:52 by mdemare          ###   ########.fr       */
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
			handle_redirec(tokens, i, cmd, data);
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

char	*rm_quotes(const char *str)
{
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	i = 0;
	if (ft_strchr(str, '\t') && str)
	{
		tmp = ft_calloc(ft_strlen(str), 1);
		len = 0;
		while (str[i])
		{
			if (str[i] != 9)
				tmp[len++] = str[i];
			i++;
		}
		return (tmp);
	}
	return (ft_strdup(str));
}
