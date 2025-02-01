/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:40:08 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/01 16:54:01 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? Check if redirection exists
int	is_redirection(char *token)
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

//? Tokenize args in the data structure
void	handle_redirection(char **tokens, int *i, t_command *cmd)
{
	if (ft_strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
		cmd->input_file = ft_strdup(tokens[++(*i)]);
	else if (ft_strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
	{
		cmd->output_file = ft_strdup(tokens[++(*i)]);
		cmd->trunc = 1;
	}
	else if (ft_strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
	{
		cmd->output_file = ft_strdup(tokens[++(*i)]);
		cmd->append = 1;
	}
	else if (ft_strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
	{
		cmd->limiter = ft_strdup(tokens[++(*i)]);
		cmd->heredoc = 1;
	}
}

//? Build cmds according to their token
t_command	*parse_command(char **tokens, int *i)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
	{
		if (is_redirection(tokens[*i]))
			handle_redirection(tokens, i, cmd);
		else
			cmd->args = add_to_tab(cmd->args, tokens[*i]);
		(*i)++;
	}
	return (cmd);
}

//? reBuild pipelines after tokenization 
t_pipeline	*parse_pipeline(char **tokens)
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
		cmd = parse_command(tokens, &i);
		if (!cmd)
		{
			free_pipeline(pipeline);
			return (NULL);
		}
		add_command_to_pipeline(pipeline, cmd);
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
	}
	return (pipeline);
}

void	print_pipeline(t_pipeline *pipeline)
{
	int			i;
	int			j;
	t_command	*cmd;

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
			printf("[%d] : Arguments: ", i);;
			while (cmd->args[j])
				printf("'%s' ", cmd->args[j++]);
			printf("\n");
		}
		if (cmd->input_file)
			printf("[%d] : Input file: %s\n", i, cmd->input_file);
		if (cmd->output_file)
			printf("[%d] : Out: %s (append: %d)\n", i, cmd->output_file, cmd->append);
		if (cmd->heredoc)
			printf("[%d] : Heredoc: enabled\n", i);
		if (cmd->limiter)
			printf("[%d] : limiter: %s\n", i, cmd->limiter);
		i++;
	}
	pipeline->cmd_count = i;
}

//<< . cat | rev >> outfile
// ./pipex file1 cmd1   cmd2   cmd3 ...   cmdn   file2
//     <   file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex here_doc LIMITER   cmd   cmd1   file
//   cmd      <<    LIMITER | cmd1   >>    file

//./pipex here_doc LIMITER cmd cmd1 file