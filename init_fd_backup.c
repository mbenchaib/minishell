/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_backup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:30:19 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/11 21:44:00 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_fd_backup(t_fd_backup *fd_backup, t_shell *shell)
{
	fd_backup->saved_stdin = dup(STDIN_FILENO);
	if (check_fail(fd_backup->saved_stdin, "dup", shell))
		return (1);
	fd_backup->saved_stdout = dup(STDOUT_FILENO);
	if (check_fail(fd_backup->saved_stdout, "dup", shell))
	{
		close (fd_backup->saved_stdin);
		return (1);
	}
	return (0);
}
