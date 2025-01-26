/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/27 00:42:57 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exit(char **argv)
{
	int exit_code;

	exit_code = g_data.exit_code;
	printf("exit\n");
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

