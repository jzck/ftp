/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_mkd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:27:35 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:19:35 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_mkd(t_ftp *ftp, char **av)
{
	if (!av[1] || av[2])
		return (console_msg(-1, "usage: mkdir <directory>"));
	FTP_CMD(ftp, "MKD %s", av[1]);
	ftp_code(ftp);
	return (0);
}
