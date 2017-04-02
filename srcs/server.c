/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:02:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/02 21:40:33 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

#define FTP_SERVER_USAGE	"%s <port>"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (-1);
	listen(sock, 42);
	return (sock);
}

int		main(int ac, char **av)
{
	int 				port;
	int					sock;
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			cslen;
	int					r;
	char				buf[1024];
	pid_t				pid;

	if (ac != 2)
		ft_usage(FTP_SERVER_USAGE, av[0]);
	port = ft_atoi(av[1]);
	if ((sock = create_server(port)) < 0)
	{
		perror(av[0]);
		return (1);
	}
	while (1)
	{
		cs = accept(sock, (struct sockaddr*)&csin, &cslen);
		if ((pid = fork()) < 0)
		{
			perror(av[0]);
			return (1);
		}
		if (pid == 0)
		{
			while ((r = read(cs, buf, 1023)) > 0)
			{
				buf[r - 1] = 0;
				ft_printf("==%i== received %i bytes: [%s]\n", getpid(), r, buf);
			}
			close(cs);
			exit (0);
		}
		close(cs);
	}
	close(sock);
	return (0);
}
