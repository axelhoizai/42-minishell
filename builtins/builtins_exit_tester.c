/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_tester.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalicem <kalicem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/26 23:07:41 by kalicem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exit_tester(char **argv)
{
	int exit_code;
	int	tmp;

	tmp = 0;
	if (argv && argv[1])
		tmp = ft_atoi(argv[1]);
	exit_code = g_data.exit_code;
	if (tmp > 0)
		exit_code = tmp;
	else if (argv && argv[1])
	{
		ft_print_error("exit", argv[1], "numeric argument required", 2);
		exit_code = 2;
	}
	rl_clear_history();
	if (argv)
		free_tab(argv);
	exit (exit_code);
}
