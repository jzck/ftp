/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:20:46 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/20 13:48:52 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static int	strisalnum(char *str)
{
	char	*s;

	s = str;
	while (*s)
	{
		if (!ft_isalnum(*s))
			return (0);
		s++;
	}
	return (1);
}

int			cmd_user(t_ftp *ftp, char **av)
{
	if (ftp->log_state == LOG_YES)
	{
		FTP_RET(ftp, "230 user '%s' logged in, proceed", ftp->username);
		return (0);
	}
	if (!strisalnum(av[1]))
		return (FTP_RET(ftp, "530 only ASCII in username"));
	ft_strcpy(ftp->username, av[1]);
	getcwd(ftp->path, 1024);
	ft_strcat(ftp->path, "/");
	ft_strcat(ftp->path, av[1]);
	console_msg(2, "userpath=%s", ftp->path);
	if ((mkdir(ftp->path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0
			&& errno != EEXIST)
			|| chdir(ftp->path) < 0)
		return (FTP_RET(ftp, "530 server doesn't have sufficient permissions"));
	FTP_RET(ftp, "230 user logged in, proceed", ftp->username);
	console_msg(1, "logon: %s@ftp://%s", ftp->username, ftp->path);
	ftp->log_state = LOG_YES;
	return (0);
}
