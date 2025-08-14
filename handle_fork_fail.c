/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork_fail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:27:44 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/13 16:59:11 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_fork(int *pipefd, int *prev_read_end)
{
	if (*prev_read_end != -1)
		close(*prev_read_end);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	fork_fail(int *pipefd, int *prev_read_end, char *cmd_path, t_shell *shell)
{
	cleanup_fork(pipefd, prev_read_end);
	free(cmd_path);
	return (check_fail(-1, "fork", shell));
}
