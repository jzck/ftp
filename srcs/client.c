/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:18:31 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/03 18:43:40 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
		return (-1);
	return (sock);
}

void	sigint_nl(int signo)
{
	(void)signo;
	ft_putchar('\n');
	signal(SIGINT, SIG_DFL);
	kill(SIGINT, getpid());
}

int		main(int ac, char **av)
{
	int 	port;
	int		sock;
	char	buf[FTP_READ_BUF];
	char	*input;
	pid_t	pid;
	pid_t	client_pid;
	int		status;

	client_pid = getpid();
	if (ac != 3)
		ft_usage(FTP_CLIENT_USAGE, av[0]);
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port)) < 0)
	{
		perror(av[0]);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if ((pid = fork()) < 0)
			exit(1);
		if (pid == 0)
		{
			signal(SIGINT, sigint_nl);
			if (!(input = readline("ft_p> ")))
				exit(1);
			if (*input)
			{
				write(sock, input, ft_strlen(input));
				read(sock, buf, FTP_READ_BUF);
				write(1, buf, ft_strlen(buf));
			}
			ft_strdel(&input);
			tcsetpgrp(STDIN, client_pid);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 1)
			return (1);
	}
	close(sock);
	return (0);
}
