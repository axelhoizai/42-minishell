/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:56:34 by mdemare           #+#    #+#             */
/*   Updated: 2025/01/24 11:05:13 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_dir(t_data *data)
{
	char	*currentpath;

	currentpath = getcwd(NULL, 0);
	printf("%s\n", currentpath);
	free(currentpath);
	data->exit_code = 0;
}
