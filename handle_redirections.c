/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:09:10 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/13 17:03:53 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_fd(char *filename, int flags, int std_fd, t_shell *shell)
{
	int			fd;
	int			ret;

	if (flags & O_CREAT)
		fd = open(filename, flags, 0644);
	else
		fd = open(filename, flags);
	if (check_fail(fd, filename, shell))
		return (1);
	ret = dup2(fd, std_fd);
	if (check_fail(ret, filename, shell))
		return (1);
	close(fd);
	return (0);
}

static int	redirect_heredoc(int fd, int std_fd, t_shell *shell)
{
	int	ret;

	ret = dup2(fd, std_fd);
	if (check_fail(ret, "heredoc", shell))
		return (1);
	close(fd);
	return (0);
}

static int	setup_redirect(int type, char *filename, t_shell *shell)
{
	if (type == TOKEN_RD_IN)
	{
		if (redirect_fd(filename, O_RDONLY, STDIN_FILENO, shell))
			return (1);
	}
	else if (type == TOKEN_RD_OUT)
	{
		if (redirect_fd(filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO,
				shell))
			return (1);
	}
	else if (type == TOKEN_APPEND)
	{
		if (redirect_fd(filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO,
				shell))
			return (1);
	}
	return (0);
}

int	handle_redirections(t_redirection *rd, t_shell *shell)
{
	while (rd)
	{
		if (rd->type == TOKEN_RD_IN)
		{
			if (setup_redirect(TOKEN_RD_IN, rd->filename_or_delimiter, shell))
				return (1);
		}
		else if (rd->type == TOKEN_RD_OUT)
		{
			if (setup_redirect(TOKEN_RD_OUT, rd->filename_or_delimiter, shell))
				return (1);
		}
		else if (rd->type == TOKEN_APPEND)
		{
			if (setup_redirect(TOKEN_APPEND, rd->filename_or_delimiter, shell))
				return (1);
		}
		else if (rd->type == TOKEN_HEREDOC && rd->heredoc_fd != -1)
		{
			if (redirect_heredoc(rd->heredoc_fd, STDIN_FILENO, shell))
				return (1);
		}
		rd = rd->next;
	}
	return (0);
}
