/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:14:51 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:37:45 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_type(t_ftp *ftp, char **av)
{
	if (!av[1])
		FTP_RET(ftp, "501 syntax error in parameter");
	if (av[1][0] == 'A')
	{
		FTP_RET(ftp, "200 type A ok");
	}
	else if (av[1][0] == 'I')
	{
		FTP_RET(ftp, "200 type I ok");
	}
	else
		FTP_RET(ftp, "500 parameter unrecognized");
	return (1);
}
