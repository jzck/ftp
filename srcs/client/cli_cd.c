/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:42:21 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 12:43:44 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_cd(t_ftp *ftp, char **av)
{
	char	*msg;

	(void)av;
	if (!av[1] || av[2])
	{
		console_msg(-1, "usage: cd <dir>");
		return (-1);
	}
	ftp_cmd(ftp, "CWD %s", av[1]);
	ftp_recv(ftp->cmd_sock, &msg);
	ft_strdel(&msg);
	return (0);
}
