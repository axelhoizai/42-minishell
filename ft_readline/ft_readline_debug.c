/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_debug.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemare <mdemare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:50:00 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/11 11:42:37 by mdemare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	debug_log(const char *format, ...)
{
	int		fd;
	va_list	args;
	char	buffer[1024];
	int		len;

	fd = open("debug_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	va_start(args, format);
	len = vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	if (len > 0)
		write(fd, buffer, len);
	close(fd);
}
