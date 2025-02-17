/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:33:31 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/17 13:41:30 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_construct_error_msg(char *builting, char *arg, char *msg)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("minishell: ");
	if (builting)
	{
		tmp = ft_strjoin(result, builting);
		free(result);
		result = ft_strjoin(tmp, ": ");
		free(tmp);
	}
	if (arg)
	{
		tmp = ft_strjoin(result, arg);
		free(result);
		result = ft_strjoin(tmp, ": ");
		free(tmp);
	}
	if (msg)
	{
		tmp = ft_strjoin(result, msg);
		free(result);
		result = tmp;
	}
	return (result);
}

// @brief 
/// @param builting ex :cd
/// @param arg ex :src
/// @param msg ex :Not a directory
/// @param exit_code ex :1

void	ft_print_error(char *builting, char *arg, char *msg)
{
	char	*result;

	result = ft_construct_error_msg(builting, arg, msg);
	if (result)
	{
		printf("%s\n", result);
		free(result);
	}
}
