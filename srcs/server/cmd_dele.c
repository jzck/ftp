/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dele.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:38:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:37:44 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_dele(t_ftp *ftp, char **av)
{
	(void)av;
	if (unlink(av[1]) < 0)
		return (FTP_RET(ftp, "550 unlink error"));
	else
		return (FTP_RET(ftp, "250 file '%s' deleted", av[1]));
	return (0);
}
