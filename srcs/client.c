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

int		g_debug = 0;

int			g_debug;
t_cmd_map	g_cli_cmd[] =
{
	{"?", cli_do_help, "print local help information"},
	{"l", cli_do_local, "execute a local command"},
	{"debug", cli_do_debug, "toggle/set debugging mode"},
	{"get", cli_do_get, "receive file"},
	{"quit", NULL, "terminate ftp session and exit"},
	{0, 0, 0},
};

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

int		do_client(int sock)
{
	char		*input;
	t_cmd_map	*cmd;
	char		**av;

	while (1)
	{
		if (!(input = readline("ft_p> ")))
			return (1);
		if (*input)
		{
			av = ft_split_whitespaces(input);
			if (!(cmd = get_cmd(av[0])))
				console_msg(-1, "?Invalid command");
			else if (cmd->f)
				(cmd->f)(sock, av);
			else
				return (0);
			ft_sstrfree(av);
		}
		ft_strdel(&input);
	}
}

int		main(int ac, char **av)
{
	int 	port;
	int		sock;

	if (ac != 3)
		ft_usage(FTP_CLIENT_USAGE, av[0]);
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port, "tcp")) < 0)
	{
		perror(av[0]);
		return (1);
	}
	do_client(sock);
	close(sock);
	return (0);
}