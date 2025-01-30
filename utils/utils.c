/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 17:07:27 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_pipe(int argc, char **argv, t_data *data)
{
	t_pipeline	*pipeline;

	pipeline = parse_pipeline(argv);
	data->exit_code = pipex(argc, argv, data->my_envp);
	print_pipeline(pipeline);
	free_pipeline(pipeline);
}

void	handle_builtins(int argc, char **argv, t_data *data)
{
	char		*cmd;

	cmd = join_argv(argv);
	// if (ft_strchr(cmd, '|'))
		// handle_pipe(argc, argv, data);
	// else 
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		change_dir(argc, argv[1], data);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		get_dir(data);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argv, data);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argc, argv[1], data);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(argv[0], "exit") == 0)
		handle_exit(argv, data);
	else if (ft_strcmp(argv[0], "clear") == 0)
		printf("\033[H\033[J");
	else if (argc >= 1)
		exec(argv, cmd, data);
	free(cmd);
}

static void	process_builtins(char *builtins, t_data *data)
{
	char	**argv;
	int		argc;

	argv = NULL;
	argc = 0;
	argv = parse_args(builtins, data);
	while (argv && argv[argc])
		argc++;
	if (argc > 0)
		handle_builtins(argc, argv, data);
	free_tab(argv);
	argc = 0;
}

char	**get_argv(const char *input, t_data *data)
{
	char	*tmp;
	char	*token;

	if (!input)
		return (NULL);
	tmp = ft_strdup(input);
	tmp = replace_double_ampersand(tmp);
	if (strchr(tmp, '\n'))
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
	free(tmp);
	return (NULL);
}
