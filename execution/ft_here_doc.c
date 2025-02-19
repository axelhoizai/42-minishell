/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoizai <ahoizai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:50:45 by mdemare           #+#    #+#             */
/*   Updated: 2025/02/19 13:38:14 by ahoizai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	limiter_count(t_pipeline *pip)
{
	int		i;
	int		j;
	int		lim_cnt;

	lim_cnt = 0;
	i = 0;
	while (pip->cmds[i])
	{
		j = 0;
		while (pip->cmds[i]->limiters && pip->cmds[i]->limiters[j])
		{
			lim_cnt++;
			j++;
		}
		i++;
	}
	return (lim_cnt);
}

static char	**hd_limiters(t_pipeline *pip)
{
	int		i;
	int		j;
	int		k;
	int		lim_cnt;
	char	**lim_tab;

	if (!pip)
		return (NULL);
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
	print_tab(lim_tab);
	return (lim_tab);
}

static void	here_doc(t_pipeline *pip, char *next_line, int lmt_cnt, int matched)
{
	int		j;
	char	**lim_tab;

	j = 0;
	lim_tab = hd_limiters(pip);
	while (j < lmt_cnt)
	{
		matched = 0;
		while (!matched)
		{
			ft_putstr_fd("here_doc> ", STDOUT_FILENO);
			next_line = get_next_line(STDIN_FILENO);
			if (!next_line)
				break ;
			if (ft_strlen(next_line) == ft_strlen(lim_tab[j]) + 1
				&& ft_strncmp(next_line, lim_tab[j],
					ft_strlen(lim_tab[j])) == 0)
				matched = 1;
			else
			{
				if (j == lmt_cnt - 1 && pip->cmds[pip->start]->heredoc)
					ft_putstr_fd(next_line, pip->cmds[pip->start]->fd_in);
			}
			free(next_line);
		}
		j++;
	}
	free_tab(lim_tab);
}

void	here_doc_init(t_pipeline *pip)
{
	char	*next_line;
	int		j;
	int		lim_cnt;
	int		matched;

	next_line = NULL;
	j = 0;
	matched = 0;
	lim_cnt = limiter_count(pip);
	if (pip->cmds[pip->start] && pip->cmds[pip->start]->heredoc == 1)
	{
		if (pip->cmds[pip->start]->fd_in > -1)
			close(pip->cmds[pip->start]->fd_in);
		pip->cmds[pip->start]->fd_in = open("here_doc", O_RDWR | O_CREAT, 0644);
	}
	if (pip->cmds[pip->start])
		here_doc(pip, next_line, lim_cnt, matched);
	if (pip->cmds[pip->start] && pip->cmds[pip->start]->heredoc == 1)
	{
		close(pip->cmds[pip->start]->fd_in);
		pip->cmds[pip->start]->fd_in = open("here_doc", O_RDONLY);
		unlink("here_doc");
	}
}

bool	is_hd(t_pipeline *pip)
{
	int	i;

	i = 0;
	while (pip->cmds[i])
	{
		if (pip->cmds[i]->limiters)
			return (true);
		i++;
	}
	return (false);
}
