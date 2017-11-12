/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:02:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:44:33 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

#define FTP_SERVER_USAGE	"%s <port>"

char	**g_av = NULL;
char	g_rootdir[PATH_MAX];

t_ftp_cmd	g_ftp_cmd[] =
{
	{"USER", cmd_user, 0},
	{"QUIT", cmd_quit, LOG_YES},
	{"RETR", cmd_retr, LOG_YES},
	{"STOR", cmd_stor, LOG_YES},
	{"CWD", cmd_cwd, LOG_YES},
	{"PASV", cmd_pasv, LOG_YES},
	{"EPSV", cmd_epsv, LOG_YES},
	{"PORT", cmd_port, LOG_YES},
	{"PWD", cmd_pwd, LOG_YES},
	{"TYPE", cmd_type, LOG_YES},
	{"LIST", cmd_list, LOG_YES},
	{"MKD", cmd_mkd, LOG_YES},
	{"RMD", cmd_rmd, LOG_YES},
	{"DELE", cmd_dele, LOG_YES},
	{0, 0, 0},
};
int		g_debug = 2;

int		ftp_cmd(t_ftp *ftp, char *msg)
{
	int		i;
	char	**av;

	i = -1;
	while (g_ftp_cmd[++i].name)
	{
		if (ft_strncmp(msg, g_ftp_cmd[i].name,
					ft_strlen(g_ftp_cmd[i].name)) == 0)
		{
			if (ftp->log_state < g_ftp_cmd[i].statelock)
				return (FTP_RET(ftp, "530 not logged in"));
			if (!(g_ftp_cmd[i].f))
				break ;
			else
			{
				av = ft_strsplit(msg, ' ');
				return (g_ftp_cmd[i].f(ftp, av));
				ft_sstrfree(av);
			}
			return (0);
		}
	}
	FTP_RET(ftp, "502 command not implemented");
	return (1);
}

int		ftp_spawn(int sock)
{
	t_ftp	ftp;
	char	*msg;

	ftp.cmd_sock = sock;
	ftp.log_state = LOG_NONE;
	ftp.d_sock = 0;
	ftp.data_state = DATA_NONE;
	FTP_RET(&ftp, "220 ready for user");
	while (ftp.cmd_sock)
	{
		ftp_recv(ftp.cmd_sock, &msg);
		ftp_cmd(&ftp, msg);
		ft_strdel(&msg);
	}
	close(ftp.cmd_sock);
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
		cslen = sizeof(csin);
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
	int		port;
	int		sock;

	g_av = av;
	getcwd(g_rootdir, PATH_MAX);
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
