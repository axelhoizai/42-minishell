/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:13:59 by ahoizai           #+#    #+#             */
/*   Updated: 2025/01/25 16:06:25 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exit(char *input, char **argv)
{
	printf("exit\n");
	rl_clear_history();
	if (input)
		free(input);
	if (argv && input)
		free_tab(argv);
	exit (0);
}
