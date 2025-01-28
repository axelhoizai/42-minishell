/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 17:40:01 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*join_argv(char **argv)
{
	int		i;
	char	*cmd;
	char	*tmp;

	if (!argv || !argv[0])
		return (NULL);
	cmd = ft_strdup(argv[0]);
	if (!cmd)
		return (NULL);
	i = 1;
	while (argv[i])
	{
		tmp = ft_strjoin(cmd, " ");
		free(cmd);
		if (!tmp)
			return (NULL);
		cmd = ft_strjoin(tmp, argv[i]);
		free(tmp);
		if (!cmd)
			return (NULL);
		i++;
	}
	return (cmd);
}

void	handle_builtins(int argc, char **argv)
{
	char	*cmd;
	t_pipeline	*pipeline;

	cmd = join_argv(argv);
	if (ft_strchr(cmd, '|'))
	{
		pipeline = parse_pipeline(argv);
		g_data.exit_code = pipex(argc, argv, g_data.my_envp);
		print_pipeline(pipeline);
		free_pipeline(pipeline);
	}
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

void	sh_tester(char *input)
{
	char	**argv;

	argv = NULL;
	while ((input = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (input)
			argv = get_argv(input);
		if (!argv)
		{
			free(input);
			continue ;
		}
		free(input);
	}
	handle_exit_tester(argv);
}

char	**get_argv(const char *input)
{
	char	**argv;
	int		argc;
	char	**builtins;
	int		i;
	char	*tmp;

	i = 0;
	argv = NULL;
	argc = 0;
	if (input)
	{
		tmp = ft_strdup(input);
		tmp = replace_double_ampersand(tmp);
		builtins = ft_split(tmp, '\n');
		while (builtins[i])
		{
			argv = parse_args(builtins[i]);
			while (argv && argv[argc])
				argc++;
			if (argc > 0)
				handle_builtins(argc, argv);
			argc = 0;
			free_tab(argv);
			i++;
			if (g_data.exit_code > 0)
				break ;
		}
		if (tmp)
			free(tmp);
		free_tab(builtins);
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**argv;
	char	*prompt;
	int		is_start;
	char	exit_code;

	is_start = 0;
	(void)ac;
	(void)av;
	argv = NULL;
	ft_init(envp, is_start);
	signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL);
	while (1)
	{
		prompt = get_promt();
		input = readline(prompt);
		exit_code = g_data.exit_code;
		free(prompt);
		if (!input)
		{
			free(input);
			handle_exit(argv);
			break ;
		}
		if (*input)
			add_history(input);
		argv = get_argv(input);
		free(input);
	}
	return (exit_code);
}
