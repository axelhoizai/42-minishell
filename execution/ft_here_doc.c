/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:50:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/21 15:54:44 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**hd_limiters(t_pipeline *pip)
{
	int		i;
	int		j;
	int		k;
	int		lim_cnt;
	char	**lim_tab;

	lim_cnt = limiter_count(pip);
	lim_tab = malloc(sizeof (char **) * (lim_cnt + 1));
	i = 0;
	k = 0;
	while (pip->cmds[i])
	{
		j = 0;
		while (pip->cmds[i]->limiters && pip->cmds[i]->limiters[j])
		{
			lim_tab[k] = ft_strdup(pip->cmds[i]->limiters[j]);
			j++;
			k++;
		}
		i++;
	}
	lim_tab[k] = NULL;
	// print_tab(lim_tab);
	return (lim_tab);
}

static bool	chck_lim(char *next_line, char *lim)
{
	if (ft_strlen(next_line) == ft_strlen(lim) + 1
		&& ft_strncmp(next_line, lim,
			ft_strlen(lim)) == 0)
		return (true);
	return (false);
}

static void	print_line(t_pipeline *pip, char *next_line, int *lmt_cnt, int *j)
{
	if (*j == *lmt_cnt - 1 && pip->cmds[pip->start]->heredoc)
	{
		ft_putstr_fd(next_line, pip->cmds[pip->start]->fd_in);
	}
}

static void	here_d(t_pipeline *pip, char *next_line, int *lmt_cnt, int matched)
{
	int		j;
	char	**lim_tab;

	j = 0;
	lim_tab = hd_limiters(pip);
	while (j < *lmt_cnt)
	{
		matched = 0;
		while (!matched)
		{
			ft_putstr_fd("here_doc> ", STDOUT_FILENO);
			next_line = get_next_line(STDIN_FILENO);
			if (!next_line)
				break ;
			if (chck_lim(next_line, lim_tab[j]))
				matched = 1;
			else
				print_line(pip, next_line, lmt_cnt, &j);
			free(next_line);
		}
		j++;
	}
	free_tab(lim_tab);
}

void	here_doc_init(t_pipeline *pip)
{
	char	*next_line;
	int		lim_cnt;
	int		matched;

	next_line = NULL;
	matched = 0;
	lim_cnt = limiter_count(pip);
	if (pip->cmds[pip->start] && pip->cmds[pip->start]->heredoc == 1)
	{
		if (pip->cmds[pip->start]->fd_in > -1)
			close(pip->cmds[pip->start]->fd_in);
		pip->cmds[pip->start]->fd_in = open("here_doc", O_RDWR | O_CREAT, 0644);
	}
	if (pip->cmds[pip->start])
		here_d(pip, next_line, &lim_cnt, matched);
	if (pip->cmds[pip->start] && pip->cmds[pip->start]->heredoc == 1)
	{
		close(pip->cmds[pip->start]->fd_in);
		pip->cmds[pip->start]->fd_in = open("here_doc", O_RDONLY);
		unlink("here_doc");
	}
}
