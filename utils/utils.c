/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 21:07:57 by kalicem          ###   ########.fr       */
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

void	handle_pipe(int argc, char **argv)
{
	t_pipeline	*pipeline;

	pipeline = parse_pipeline(argv);
	g_data.exit_code = pipex(argc, argv, g_data.my_envp);
	print_pipeline(pipeline);
	free_pipeline(pipeline);
}

void	handle_builtins(int argc, char **argv)
{
	char		*cmd;

	cmd = join_argv(argv);
	if (ft_strchr(cmd, '|'))
		handle_pipe(argc, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		change_dir(argc, argv[1]);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		get_dir();
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argc, argv[1]);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(argv[0], "exit") == 0)
		handle_exit(argv);
	else if (ft_strcmp(argv[0], "clear") == 0)
		printf("\033[H\033[J");
	else if (argc >= 1)
		exec(argv, cmd, g_data.my_envp);
	free(cmd);
}

static void	process_builtins(char **builtins)
{
	char	**argv;
	int		argc;
	int		i;

	argv = NULL;
	argc = 0;
	i = 0;
	while (builtins && builtins[i])
	{
		argv = parse_args(builtins[i]);
		while (argv && argv[argc])
			argc++;
		if (argc > 0)
			handle_builtins(argc, argv);
		free_tab(argv);
		argc = 0;
		if (g_data.exit_code > 0)
			break ;
		i++;
	}
}

char	**get_argv(const char *input)
{
	char	**builtins;
	char	*tmp;

	if (!input)
		return (NULL);
	tmp = ft_strdup(input);
	tmp = replace_double_ampersand(tmp);
	builtins = ft_split(tmp, '\n');
	free(tmp);
	process_builtins(builtins);
	free_tab(builtins);
	return (NULL);
}
