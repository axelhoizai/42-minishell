/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:16:24 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/12 17:39:50 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	main_loop(t_data *data)
// {
// 	char		*input;
// 	char		exit_code;
// 	// char		*prompt;
// 	t_rl		rl;

// 	init_readline(&rl);
// 	get_data(data);
// 	data->term = rl.term;
// 	while (1)
// 	{
// 		rl.prompt = get_prompt(data->env_ms);
// 		input = ft_readline(&rl);
// 		if (!input)
// 		{
// 			// disable_raw_mode();
// 			// free_var(rl.prompt);
// 			handle_exit(NULL, data);
// 			break ;
// 		}
// 		get_argv(input, data);
// 		free_var(input);
// 		// free(input;
// 		// rl.buffer_size = 0;
// 		// ft_bzero(rl.buffer, rl.buffer_size);
		
// 		exit_code = data->exit_code;
// 	}
// 	// disable_raw_mode();
// 	free_history(&rl);
// 	return (exit_code);
// }

char	main_loop(t_data *data)
{
	char	*input;
	char	*prompt;
	char	exit_code;

	while (1)
	{
		prompt = get_prompt(data->env_ms);
		input = readline(prompt);
		exit_code = data->exit_code;
		free(prompt);
		if (!input)
		{
			free(input);
			handle_exit(NULL, data);
			break ;
		}
		if (*input)
			add_history(input);
		get_argv(input, data);
		// free(input);
		free_var(input);
	}
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
	// if (ac > 1)
	// 	sh_tester(NULL, &data);
	exit_code = main_loop(&data);
	return (exit_code);
}
