/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/10 19:53:05 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	main_loop(t_data *data)
{
	char		*input;
	char		exit_code;
	// char		*prompt;
	t_rl		rl;

	init_readline(&rl);
	get_data(data);
	data->term = rl.term;
	while (1)
	{
		// if (rl.prompt)
		// 	free(rl.prompt);
		rl.prompt = get_prompt(data->env_ms);
		// write(STDOUT_FILENO, readline.prompt, ft_strlen(readline.prompt));
		input = ft_readline(&rl);
		if (!input)
		{
			// free_readline(&rl);
			disable_raw_mode();
			handle_exit(NULL, data);
			break ;
		}
		get_argv(input, data);
		free(input);
		exit_code = data->exit_code;
	}
	// free_readline(&rl);
	disable_raw_mode();
	return (exit_code);
}

// char	main_loop(t_data *data)
// {
// 	char	*input;
// 	char	*prompt;
// 	char	exit_code;

// 	while (1)
// 	{
// 		prompt = get_prompt(data->env_ms);
// 		input = readline(prompt);
// 		exit_code = data->exit_code;
// 		free(prompt);
// 		if (!input)
// 		{
// 			free(input);
// 			handle_exit(NULL, data);
// 			break ;
// 		}
// 		if (*input)
			// add_history(input);
// 		get_argv(input, data);
// 		free(input);
// 	}
// 	return (exit_code);
// }

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
	// if (ac > 1)
	// 	sh_tester(NULL, &data);
	exit_code = main_loop(&data);
	return (exit_code);
}
