/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_stdio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:31:23 by mben-cha          #+#    #+#             */
/*   Updated: 2025/08/11 21:44:58 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restore_stdio(int saved_stdin, int saved_stdout, t_shell *shell)
{
	int	ret;

	ret = dup2(saved_stdin, STDIN_FILENO);
	if (check_fail(ret, "dup2", shell))
		return (1);
	close(saved_stdin);
	ret = dup2(saved_stdout, STDOUT_FILENO);
	if (check_fail(ret, "dup2", shell))
		return (1);
	close(saved_stdout);
	return (0);
}
