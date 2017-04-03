/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:42:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/03 17:20:02 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_stof	g_ftp_cmdlist[] =
{
	{"ls", NULL},
	{0, 0},
};

int		ftp_cmd(char *cmd, t_ftp_reply *reply)
{
	char	**av;
	int		i;

	reply->code = 0;
	av = ft_split_whitespaces(cmd);
	i = -1;
	while (g_ftp_cmdlist[++i].key)
	{
		if (ft_strcmp(g_ftp_cmdlist[i].key, av[0]) == 0)
		{
			ft_asprintf(&reply->data, "%s: Valid command !!!\n", av[0]);
			return (0);
		}
	}
	ft_asprintf(&reply->data, "%s: ?Invalid command\n", av[0]);
	return (0);
}
