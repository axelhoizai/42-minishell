/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 11:26:10 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit_tester(char **argv)
{
	int	exit_code;

	exit_code = g_data.exit_code;
	if (argv && argv[1] && ft_isnumeric(argv[1]) == 1)
		exit_code = ft_atoi(argv[1]);
	else if (argv && argv[1])
	{
		ft_print_error("exit", argv[1], "numeric argument required", 2);
		exit_code = 2;
	}
	rl_clear_history();
	if (argv)
		free_tab(argv);
	ms_lstclear(&g_data.env_ms);
	exit(exit_code);
}

int	argc_from_argv(char **argv)
{
	int	count;

	count = 2;
	while (argv && argv[count])
		count++;
	return (count);
}

char	*join_argv2(char **argv)
{
	int		i;
	char	*cmd;
	char	*tmp;

	if (!argv || !argv[1])
		return (NULL);
	cmd = ft_strdup(argv[1]);
	if (!cmd)
		return (NULL);
	i = 2;
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

void	handle_av_commands(char **av)
{
	char	**argv;

	if (av && av[2])
	{
		printf("Usage tester: ./minishell \"cmds\"\n");
		handle_exit_tester(NULL);
		return ;
	}
	argv = get_argv(av[1]);
	handle_exit_tester(argv);
	free_tab(argv);
}

void	sh_tester(char **av)
{
	char	**argv;
	char	*input;

	argv = NULL;
	if (!isatty(STDIN_FILENO))
	{
		input = get_next_line(STDIN_FILENO);
		while (input != NULL)
		{
			argv = get_argv(input);
			if (!argv)
			{
				free(input);
				input = get_next_line(STDIN_FILENO);
				continue ;
			}
			free(input);
			input = get_next_line(STDIN_FILENO);
		}
	}
	else
		handle_av_commands(av);
	handle_exit_tester(argv);
}
