#include "ft_p.h"

char	**environ;

int		cli_do_local(int sock, char **av)
{
	pid_t	pid;
	char	*cmd[4];

	(void)sock;
	av++;
	if ((pid = fork()) < 0)
		return (1);
	if (pid == 0)
	{
		cmd[0] = "/bin/sh";
		cmd[1] = "-c";
		cmd[2] = ft_sstrcat(av, ' ');
		cmd[3] = NULL;
		console_msg(3, "inside pid cmd=[%s]", cmd[2]);
		execve(cmd[0], cmd, environ);
		console_msg(3, "execve(2) error: %s", strerror(errno));
		exit(42);
	}
	console_msg(3, "waiting for local command");
	waitpid(pid, NULL, 0);
	return (0);
}
