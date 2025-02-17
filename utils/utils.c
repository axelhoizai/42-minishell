/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 11:23:06 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//? Check if pipe exists
bool	is_pipe(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '|'))
		{
			free_tab(argv);
			return (true);
		}
		i++;
	}
	free_tab(argv);
	return (false);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd, "clear") == 0)
		return (true);
	return (false);
}

void	handle_builtins(t_command *cmd, t_pipeline *pip, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->arg_cnt, cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		change_dir(cmd->arg_cnt, cmd->args, pip, data);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		get_dir(data, pip);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd->args, data);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd->arg_cnt, cmd->args, pip, data);
	else if (ft_strcmp(cmd->args[0], "env") == 0 && cmd->args[1])
		ft_print_error(NULL, NULL, "Use \'env\' with no options or arguments");
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(data, pip);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		handle_exit(pip, data);
	else if (ft_strcmp(cmd->args[0], "clear") == 0)
		printf("\033[3J\033[H\033[J");
}

//! Faire une fonction exclusivement handle_builtins
//TODO : Send all builtins in the exec part
void	send_to_exec(int argc, char **argv, t_data *data)
{
	t_pipeline	*pip;
	int			fd_std;

	(void)argc;
	fd_std = -1;
	pip = parse_pipeline(argv, data);
	print_pipeline(pip);
	if (is_pipe(argv))
	{
		data->exit_code = pipex(pip, data);
		free_pipeline(pip);
	}
	else if (is_builtin(pip->cmds[0]->args[0]))
	{
		if (pip->cmds[0]->fd_out > -1)
		{
			fd_std = dup(STDOUT_FILENO);
			dup2(pip->cmds[0]->fd_out, STDOUT_FILENO);
			close(pip->cmds[0]->fd_out);
		}
		if (pip->cmds[0]->out_error == 0 && pip->cmds[0]->in_error == 0)
			handle_builtins(pip->cmds[0], pip, data);
		if (pip->cmds[0]->output_file)
		{
			dup2(fd_std, STDOUT_FILENO);
			if (fd_std != -1)
				close(fd_std);
		}
		free_pipeline(pip);
	}
	else if (argv)
	{
		if (pip->cmds[0]->heredoc == 1)
			here_doc(pip->cmds[0]);
		exec(pip, data);
		if (pip)
			free_pipeline(pip);
	}
}

//? Parse builtins to removes quotes and parse dollars
static void	process_builtins(char *builtins, t_data *data)
{
	char	**argv;
	int		argc;

	argv = NULL;
	argc = 0;
	argv = parse_args(builtins, data);
	free(builtins);
	if (argv && !argv[0])
	{
		free(argv);
		data->exit_code = 0;
		return ;
	}
	while (argv && argv[argc])
		argc++;
	if (argc > 0)
		send_to_exec(argc, argv, data);
}

//? Get the input and 
void	get_argv(char *input, t_data *data)
{
	char	*tmp;
	char	*token;

	if (!input)
		return ;
	tmp = ft_strdup(input);
	if (tmp && ft_strlen(tmp) == 0)
	{
		free(tmp);
		return ;
	}
	tmp = replace_double_ampersand(tmp);
	if (ft_strchr(tmp, '\n'))
	{
		token = strtok(tmp, "\n");
		while (token)
		{
			process_builtins(token, data);
			if (data->exit_code > 0)
				break ;
			token = strtok(NULL, "\n");
		}
	}
	else
		process_builtins(tmp, data);
}
