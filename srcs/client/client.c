/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:18:31 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/09 14:53:06 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

t_cmd_map	g_cli_cmd[] =
{
	{"ls", cli_ls, "list contents of remote directory"},
	{"user", cli_user, "authentify user by name"},
	/* {"cd", cli_do_cd, "change remote working directory"}, */
	/* {"get", cli_do_get, "receive file"}, */
	/* {"put", cli_do_put, "send one file"}, */
	/* {"pwd", cli_do_sh, "print working directory on remote machine"}, */
	{"quit", NULL, "terminate ftp session and exit"},

	{"?", cli_help, "print local help information"},
	{"debug", cli_debug, "set debugging level"},
	/* {"l", cli_do_local, "execute a local command"}, */
	{0, 0, 0},
};
int		g_debug = 1;

t_cmd_map	*get_cmd(char *cmd)
{
	int		i;

	i = -1;
	while (g_cli_cmd[++i].key)
	{
		if (ft_strcmp(g_cli_cmd[i].key, cmd) == 0)
			return (&g_cli_cmd[i]);
	}
	return (NULL);
}

int			do_client(t_ftp *ftp)
{
	char		*input;
	t_cmd_map	*cmd;
	char		**av;
	int			code;

	code = ftp_code(ftp);
	while (1)
	{
		if (!(input = readline("ftp> ")))
			return (1);
		if (*input)
		{
			av = ft_split_whitespaces(input);
			if (!(cmd = get_cmd(av[0])))
				console_msg(-1, "?Invalid command");
			else if (cmd->f)
				code = (cmd->f)(ftp, av);
			else
				return (0);
			ft_sstrfree(av);
		}
		ft_strdel(&input);
	}
}

int			main(int ac, char **av)
{
	int		port;
	int		sock;
	t_ftp	ftp;

	if (ac != 3)
		ft_usage(FTP_CLIENT_USAGE, av[0]);
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port, "tcp")) < 0)
	{
		perror(av[0]);
		return (1);
	}
	ftp.cmd_sock = sock;
	ftp.data_state = DATA_NONE;
	ftp.d_sock = 0;
	do_client(&ftp);
	close(sock);
	return (0);
}
