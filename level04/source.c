#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <signal.h>

int main(void)
{
	int		wstatus;
	char	buffer[128];
	pid_t	pid;

	pid = fork();
	bzero(buffer, 128);

	if (pid == 0)
	{
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
	}
	else
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus))
		{
			puts("child is exiting...");
			return(0);
		}
		while (1)
		{
			if (ptrace(PTRACE_PEEKUSER, pid, 0x2c, 0) == 11)
			{
				puts("no exec() for you");
				kill(pid, 9);
				break;
			}
		}
	}
	return (0);
}
