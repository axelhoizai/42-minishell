/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/28 21:07:48 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_tester(char *input)
{
	char	**argv;

	argv = NULL;
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
	handle_exit_tester(argv);
}

char	main_loop(char **argv)
{
	char	*input;
	char	*prompt;
	char	exit_code;

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

int	main(int ac, char **av, char **envp)
{
	char	**argv;
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
	exit_code = main_loop(argv);
	return (exit_code);
}
