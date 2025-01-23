/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:33:31 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/23 19:49:06 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief 
/// @param builting ex :cd
/// @param arg ex :src
/// @param msg ex :Not a directory
/// @param exit_code ex :1
void	ft_print_error(char *builting, char *arg, char *msg, int exit_code)
{
	char	*result;
	char	*tmp1;
	char	*tmp2;

	tmp2 = NULL;
	result = ft_strdup("minishell: ");
	if (builting)
	{
		tmp1 = ft_strjoin(result, builting);
		tmp2 = ft_strjoin(tmp1, ": ");
		free(tmp1);
	}
	if (arg)
	{
		tmp1 = ft_strjoin(tmp2, arg);
		free(tmp2);
		tmp2 = ft_strjoin(tmp1, ": ");
		free(tmp1);
	}
	if (msg)
	{
		free(result);
		result = ft_strjoin(tmp2, msg);
	}
	free(tmp2);
	printf("%s\n", result);
	free(result);
	printf("exit_code = %d\n", exit_code);
}
