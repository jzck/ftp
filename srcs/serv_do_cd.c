/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_do_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:08:05 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:08:41 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	g_rootdir[PATH_MAX];

int		serv_do_cd(int sock)
{
	char	path[MAXLINE];
	char	*abspath;
	int		ret;
	char	*ok;

	if ((ret = read(sock, path, MAXLINE)) < 0)
		return (CMD_FAIL);
	path[ret] = 0;
	DG("received 'cd %s' command", path);
	ok = NULL;
	if (!(abspath = realpath(path, ok)))
		return (CD_DIR_NOT_FOUND);
	ft_strcpy(path, abspath);
	if (!*abspath)
		return (CD_DIR_NOT_FOUND);
	ft_strdel(&abspath);
	DG("absolute path is '%s'", path);
	DG("root dir is '%s'", g_rootdir);
	if (!ft_strstr(path, g_rootdir))
		return (CD_RESTRICTED_DIR);
	return (chdir(path) ? CMD_FAIL : CMD_SUCCESS);
}
