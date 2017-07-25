#include "ft_p.h"

int		serv_do_cd(int sock)
{
	char	*oldpwd;
	char 	path[MAXLINE];
	int		ret;

	if ((ret = read(sock, path, MAXLINE)) < 0)
		return (CMD_FAIL);

	DG("received 'cd %s' command", path);

	oldpwd = getcwd(NULL, 0);
	(void)oldpwd;
	return(chdir(path) ? CMD_FAIL : CMD_SUCCESS);
}
