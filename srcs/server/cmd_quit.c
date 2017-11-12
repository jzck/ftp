/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:20:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:37:45 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_quit(t_ftp *ftp, char **av)
{
	(void)av;
	close(ftp->cmd_sock);
	ftp->cmd_sock = 0;
	FTP_RET(ftp, "221 service closing control connection");
	return (1);
}
