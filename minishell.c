/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/29 17:06:11 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	main_loop(char **argv, t_data *data)
{
	char	*input;
	char	*prompt;
	char	exit_code;

	while (1)
	{
		prompt = get_promt();
		input = readline(prompt);
		exit_code = data->exit_code;
		free(prompt);
		if (!input)
		{
			free(input);
			handle_exit(argv, data);
			break ;
		}
		if (*input)
			add_history(input);
		argv = get_argv(input, data);
		free(input);
	}
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	char	**argv;
	int		is_start;
	char	exit_code;
	t_data	data;

	is_start = 0;
	exit_code = 0;
	(void)ac;
	(void)av;
	argv = NULL;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL, &data);
	exit_code = main_loop(argv, &data);
	return (exit_code);
}
