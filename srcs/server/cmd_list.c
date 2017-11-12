/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:22:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 11:24:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_list(t_ftp *ftp, char **av)
{
	pid_t	pid;
	int		status;

	if (dconn_open(ftp) < 0)
		return (-1);
	if ((pid = fork()) < 0)
		perror("fork");
	else if (pid == 0)
	{
		dup2(ftp->d_sock, 1);
		execl("/bin/ls", "ls", "-lA", av[1], NULL);
	}
	waitpid(pid, &status, 0);
	return (dconn_close(ftp));
}
