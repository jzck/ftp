/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:36:24 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:37:44 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_cwd(t_ftp *ftp, char **av)
{
	char	buf[1024];
	char	old[1024];

	getcwd(old, 1024);
	if (chdir(av[1]))
	{
		console_msg(1, "chdir(%s) failed errno=%i", av[1], errno);
		FTP_RET(ftp, "550 directory not found");
	}
	else
	{
		getcwd(buf, 1024);
		if (!ft_strstr(buf, ftp->path))
		{
			console_msg(0, "%s -> %s", buf, ftp->path);
			chdir(old);
			FTP_RET(ftp, "550 unauthorized directory");
		}
		else
			FTP_RET(ftp, "200 success");
	}
	return (0);
}
