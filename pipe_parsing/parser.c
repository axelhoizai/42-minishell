/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:40:08 by kalicem           #+#    #+#             */
/*   Updated: 2025/02/13 16:02:44 by ahoizai          ###   ########.fr       */
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
void	handle_redirection(char **tokens, int *i, t_command *cmd, t_data *data)
{
	if (ft_strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
	{
		if (cmd->input_file || cmd->in_error == 1)
		{
			if (cmd->fd_in > -1)
				close(cmd->fd_in);
			free(cmd->input_file);
		}
		cmd->input_file = ft_strdup(tokens[++(*i)]);
		cmd->fd_in = open_file(NULL, cmd->input_file, 1, NULL);
		if (cmd->fd_in == -1 || cmd->in_error == 1)
		{
			if (cmd->fd_in == -1)
			{
				if (cmd->in_error == 0)
					ft_print_error(NULL, cmd->input_file, "No such file or directory");
				cmd->in_error = 1;
				// free(cmd->input_file);
			}
			else
			{
				close(cmd->fd_in);
				cmd->fd_in = -1;
			}
			data->exit_code = EXIT_FAILURE;
		}
	}
	else if (ft_strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
	{
		cmd->trunc = 1;
		if (cmd->fd_out > -1 || cmd->output_file)
		{
			if (cmd->fd_out > -1)
				close(cmd->fd_out);
			free(cmd->output_file);
		}
		cmd->output_file = ft_strdup(tokens[++(*i)]);
		if (cmd->out_error == 0)
			cmd->fd_out = open_outfile(cmd->output_file, data, 0);
		printf("fd_out : %d\n", cmd->fd_out);
		if (cmd->fd_out == -1 && cmd->out_error == 0)
		{
			if (cmd->in_error == 0)
			{
				if (cmd->out_error == 0)
					ft_print_error(NULL, cmd->output_file, "No such file or directory");
				cmd->fd_out = open("/dev/null", O_RDONLY); //test
				close(cmd->fd_out);
				cmd->fd_out = -1; //test pour null
				// free(cmd->output_file);
			}
			if (cmd->fd_in > -1)
				close(cmd->fd_in);
			cmd->out_error = 1;
			data->exit_code = EXIT_FAILURE;
		}
		if (cmd->in_error == 1)
		{
			if (cmd->fd_out > -1)
				close(cmd->fd_out);
		}	
	}
	else if (ft_strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
	{
		cmd->append = 1;
		if (cmd->fd_out > -1 || cmd->output_file)
		{
			if (cmd->fd_out > -1)
				close(cmd->fd_out);
			free(cmd->output_file);
		}
		cmd->output_file = ft_strdup(tokens[++(*i)]);
		if (cmd->out_error == 0)
			cmd->fd_out = open_outfile(cmd->output_file, data, 1);
		if (cmd->fd_out == -1 && cmd->out_error == 0)
		{
			if (cmd->in_error == 0)
			{
				if (cmd->out_error == 0)
					ft_print_error(NULL, cmd->output_file, "No such file or directory");
				cmd->fd_out = open("/dev/null", O_RDONLY); //test
				close(cmd->fd_out);
				cmd->fd_out = -1; //test pour null
				// free(cmd->output_file);
			}
			if (cmd->fd_in > -1)
				close(cmd->fd_in);
			cmd->out_error = 1;
			data->exit_code = EXIT_FAILURE;
		}
		if (cmd->in_error == 1)
		{
			if (cmd->fd_out > -1)
				close(cmd->fd_out);
		}	
	}
	// else if (ft_strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
	// {
	// 	cmd->limiter = ft_strdup(tokens[++(*i)]);
	// 	cmd->heredoc = 1;
	// }
	else if (ft_strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
	{
		cmd->limiters = add_to_tab(cmd->limiters, tokens[++(*i)]);
		cmd->heredoc = 1;
	}

}

//? Build cmds according to their token
t_command	*parse_command(char **tokens, int *i, t_data *data)
{
	t_command	*cmd;
	int			j;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
	{
		if (is_redirection(tokens[*i]))
		{
			handle_redirection(tokens, i, cmd, data);
			printf("cmd->out_error : %d\n", cmd->out_error);
			// if (cmd->in_error == 1 || cmd->out_error == 1)
			// 	return (cmd);
		}
		else
		{
			cmd->args = add_to_tab(cmd->args, tokens[*i]);
			cmd->arg_cnt += 1;
		}
		(*i)++;
	}
	j = 1;
	while (cmd->args[j])
	{
		if (cmd->args[j][0] != '-' && !is_builtin(cmd->args[0]))
		{
			cmd->fd_in = open_file(data, cmd->args[j], 1, NULL);
			if (cmd->fd_in == -1)
				ft_print_error(NULL, cmd->args[j], "No such file or directory");
		}
		j++;
	}
	return (cmd);
}

//? reBuild pipelines after tokenization 
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
		// if (cmd->in_error == 1 || cmd->out_error == 1)
		// {
		// 	// free_command(cmd);
		// 	return (pipeline);
		// }
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
			printf("arg_cnt : %d\n", cmd->arg_cnt);
		}
		if (cmd->input_file)
			printf("[%d] : Input file: %s\n", i, cmd->input_file);
		if (cmd->output_file)
			printf("[%d] : Out: %s (append: %d)\n", i, cmd->output_file, cmd->append);
		if (cmd->heredoc)
			printf("[%d] : Heredoc: enabled\n", i);
		// if (cmd->limiter)
		// 	printf("[%d] : limiter: %s\n", i, cmd->limiter);
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
	printf("pipeline->pipe_cnt: %d\n", pipeline->pipe_cnt);

	pipeline->cmd_count = i;
}

//<< . cat | rev >> outfile
// ./pipex file1 cmd1   cmd2   cmd3 ...   cmdn   file2
//     <   file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex here_doc LIMITER   cmd   cmd1   file
//   cmd      <<    LIMITER | cmd1   >>    file

//./pipex here_doc LIMITER cmd cmd1 file