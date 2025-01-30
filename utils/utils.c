/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:52:32 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/30 15:16:48 by ahoizai          ###   ########.fr       */
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

void	handle_pipe(char **argv, t_data *data)
{
	t_pipeline	*pipeline;

	pipeline = parse_pipeline(argv);
	free_tab(argv);
	print_pipeline(pipeline);
	data->exit_code = pipex(pipeline, data);
	free_pipeline(pipeline);
}

void	handle_builtins(int argc, char **argv, t_data *data)
{
	int			is_pipe = 0;
	int 		i = 0;

	while (argv[i])
	{
		if (ft_strchr(argv[i], '|'))
		{
			is_pipe = 1;
			break ;
		}
		i++;
	}
	if (is_pipe == 1)
		handle_pipe(argv, data);
	else if (ft_strcmp(argv[0], "echo") == 0)
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
		exec(argv, data);
	// if (cmd)
	// 	free(cmd);
}

static void	process_builtins(char *builtins, t_data *data)
{
	char	**argv;
	int		argc;

	argv = NULL;
	argc = 0;
	// while (builtins && builtins[i])
	// {
		argv = parse_args(builtins, data);
		free(builtins);
		while (argv && argv[argc])
			argc++;
		if (argc > 0)
			handle_builtins(argc, argv, data);
		// free_tab(argv);
		argc = 0;
	// 	if (data->exit_code > 0)
	// 		break ;
	// 	i++;
	// }
}

char	**get_argv(const char *input, t_data *data)
{
	char	**builtins;
	char	*tmp;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	tmp = ft_strdup(input);
	if (ft_strstr(tmp, "&&"))
		tmp = replace_double_ampersand(tmp);
	if (!ft_strchr(tmp, '\n'))
		process_builtins(tmp, data);
	else
	{
		builtins = ft_split(tmp, '\n');
		free(tmp);
		while (builtins && builtins[i])
		{
			process_builtins(builtins[i], data);
			if (data->exit_code > 0)
				break ;
			i++;
		}
		free_tab (builtins);
	}
	return (NULL);
}
