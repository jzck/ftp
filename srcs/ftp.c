/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:08:44 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/03 18:24:24 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char		**g_av;

int		ftp_reply(int sock, t_ftp_reply *reply)
{
	write(sock, reply->data, ft_strlen(reply->data));
	return (0);
}

int		ftp_spawn(int cs)
{
	int			r;
	char		buf[1024];
	t_ftp_reply	reply;

	ft_printf("{yel}{inv}%i {gre} new connection {eoc}\n", getpid());
	while ((r = read(cs, buf, FTP_BUF)) > 0)
	{
		buf[r] = 0;
		ft_printf("{yel}{inv}%i {eoc} received %i bytes: [%s]\n", getpid(), r, buf);
		ft_bzero(&reply, sizeof(reply));
		ftp_cmd(buf, &reply);
		ftp_reply(cs, &reply);
	}
	ft_printf("{yel}{inv}%i {red} end of connection {eoc}\n", getpid());
	close(cs);
	return (0);
}

int		ftp_daemon(int sock)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			cslen;
	pid_t				pid;

	while (1)
	{
		cs = accept(sock, (struct sockaddr*)&csin, &cslen);
		if ((pid = fork()) < 0)
		{
			perror(g_av[0]);
			return (1);
		}
		if (pid == 0)
			exit(ftp_spawn(cs));
		close(cs);
	}
	close(sock);
	return (0);
}
