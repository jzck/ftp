/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:04:01 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 15:09:21 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_help(t_ftp *ftp, char **av)
{
	int			i;
	t_cmd_map	*cmd;

	(void)ftp;
	if (!av[1])
	{
		i = -1;
		while (g_cli_cmd[++i].key)
			console_msg(0, "%s:\t%s", g_cli_cmd[i].key, g_cli_cmd[i].help);
	}
	else
	{
		i = 0;
		while (av[++i])
		{
			cmd = get_cmd(av[i]);
			if (cmd)
				console_msg(0, "%s:\t%s", cmd->key, cmd->help);
			else
				console_msg(0, "%s:\tinvalid command", av[i]);
		}
	}
	return (0);
}
