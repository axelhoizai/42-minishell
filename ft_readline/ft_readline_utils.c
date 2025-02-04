/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:34:22 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/04 10:20:44 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*get_data(t_data *new_data)
{
	static t_data	*data = NULL;

	if (new_data)
		data = new_data;
	return (data);
}

t_rl	*get_rl(t_rl *new_readline)
{
	static t_rl *readline = NULL;

	if (new_readline)
		readline = new_readline;
	return (readline);
}

t_data_term	*get_term_data(t_data_term *new_term)
{
	static t_data_term term;

	if (new_term) 
		term = *new_term;
	return (&term);
}

char	*expand_buffer(char *buffer, int *capacity)
{
	char	*new_buffer;
	int		i;

	*capacity *= 2;
	new_buffer = (char *)ft_calloc(*capacity, 1);
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

void	print_prompt(t_rl *readline)
{
	move_cursor(readline->prompt_row , readline->prompt_col);
	write(STDOUT_FILENO, "\r", 1);
	write(STDOUT_FILENO, readline->prompt, readline->prompt_len);
	write(STDOUT_FILENO, "\033[K", 3);
	fflush(stdout);
}
