/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/01 17:30:11 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	main_loop(char **argv, t_data *data)
{
	char		*input;
	char		exit_code;
	t_rl		readline;

	init_readline(&readline);
	get_data(data);
	data->term = readline.term;
	while (1)
	{
		if (readline.prompt)
        	free(readline.prompt);
		readline.prompt = get_prompt(data->env_ms);
		write(STDOUT_FILENO, readline.prompt, ft_strlen(readline.prompt));
		input = ft_realine(&readline);
		if (!input)
		{
			free_readline(&readline);
			handle_exit(argv, data);
			break ;
		}
		argv = get_argv(input, data);
		data->argv = argv;
		free(input);
		exit_code = data->exit_code;
	}
	free_readline(&readline);
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	int		is_start;
	char	exit_code;
	t_data	data;

	is_start = 0;
	exit_code = 0;
	(void)ac;
	(void)av;
	ft_bzero(&data, sizeof(t_data));
	ft_init(envp, &is_start, &data);
	// signal(SIGINT, handle_sigint);
	if (ac > 1)
		sh_tester(NULL, &data);
	exit_code = main_loop(NULL, &data);
	return (exit_code);
}
