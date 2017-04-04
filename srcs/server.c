/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:02:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/03 16:42:49 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

#define FTP_SERVER_USAGE	"%s <port>"

char	**g_av = NULL;
t_itof	g_ftp_cmd[] =
{
	{REQUEST_FILE, serv_do_get},
	{0, 0},
};

int		ftp_cmd(int sock, int req)
{
	int		i;
	int		msg_ok;

	i = -1;
	msg_ok = htons(CMD_SUPPORTED);
	while (g_ftp_cmd[++i].id)
	{
		if (g_ftp_cmd[i].id == req)
		{
			if (!(g_ftp_cmd[i].f))
				break ;
			write(sock, (char *)&msg_ok, sizeof(msg_ok));
			(g_ftp_cmd[i].f)(sock);
			return (0);
		}
	}
	msg_ok = htons(CMD_NOT_SUPPORTED);
	write(sock, (char *)&msg_ok, sizeof(msg_ok));
	return (1);
}

int		ftp_spawn(int sock)
{
	int		req;
	int		r;

	DG("new connection");
	while ((r = read(sock, (char*)&req, sizeof(req))) > 0)
	{
		req = ntohs(req);
		DG("request code [%i]", req);
		ftp_cmd(sock, req);
	}
	DG("end of connection");
	close(sock);
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
			return (-1);
		if (pid == 0)
		{
			close(sock);
			exit(ftp_spawn(cs));
		}
		close(cs);
	}
	close(sock);
	return (0);
}

int		main(int ac, char **av)
{
	int 				port;
	int					sock;

	g_av = av;
	if (ac != 2)
		ft_usage(FTP_SERVER_USAGE, av[0]);
	port = ft_atoi(av[1]);
	if ((sock = create_server(port, 3, "tcp")) < 0
			|| ftp_daemon(sock) < 0)
	{
		perror(av[0]);
		return (1);
	}
	return (0);
}
