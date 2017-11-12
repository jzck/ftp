/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_dele.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:41:33 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:19:35 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_dele(t_ftp *ftp, char **av)
{
	if (!av[1] || av[2])
		return (console_msg(-1, "usage: unlink <directory>"));
	FTP_CMD(ftp, "DELE %s", av[1]);
	ftp_code(ftp);
	return (0);
}
