/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mkd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:17:53 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:37:45 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_mkd(t_ftp *ftp, char **av)
{
	if (mkdir(av[1], 0755) < 0)
		return (FTP_RET(ftp, "550 mkdir() error"));
	return (FTP_RET(ftp, "257 '%s' created", av[1]));
}
