/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:43:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 19:58:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_ls(t_ftp *ftp, char **av)
{
	(void)sock;
	(void)av;
	int		status;
	int		code;

	cli_send(ftp, "LIST -a");
	ftp_dconn(ftp);
	if ((pid = fork()) < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(1, ftp->d_sock);
		wait(&status);
	}
	code = ftp_code(ftp);
	kill(pid, SIGSTOP);
	return (0);
}
