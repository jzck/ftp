/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:20:46 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 15:14:02 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_user(t_ftp *ftp, char **av)
{
	ft_strcpy(ftp->username, av[1]);
	ft_strcpy(ftp->path, REPOPATH);
	ft_strcat(ftp->path, av[1]);
	if (mkdir(ftp->path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0
			&& chdir(ftp->path) < 0)
		return (ftp_ret(ftp, "530 mkdir/chdir"));
	if (getcwd(ftp->path, 100) < 0)
		return (ftp_ret(ftp, "530 getcwd"));
	ftp_ret(ftp, "230 user '%s' logged in, proceed", ftp->username);
	console_msg(1, "logon: %s@ftp://%s", ftp->username, ftp->path);
	ftp->log_state = LOG_YES;
	return (0);
}