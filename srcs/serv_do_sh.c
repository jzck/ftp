#include "ft_p.h"

int		serv_do_sh(int sock)
{
	char 	command[MAXLINE];
	int		ret;

	if ((ret = read(sock, command, MAXLINE)) < 0)
		return (CMD_FAIL);
	command[ret] = 0;
	DG("received '%s' command", command);
	if (fork() == 0)
	{
		dup2(sock, 1);
		system(command);
		exit(0);
	}
	DG("waiting for command");
	wait(0);
	DG("finished waiting for command");
	return (CMD_SUCCESS);
}

