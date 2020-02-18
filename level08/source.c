#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void	log_wrapper(FILE *f, char *msg, char *s)
{
	char buffer[254];

	strcpy(buffer, msg);
	snprintf(buffer + strlen(buffer), 254 - strlen(buffer), s);
	buffer[strcspn(buffer, "\n")] = '\0';
	fprintf(f, "LOG: %s\n", buffer);
}

int		main(int argc, char **argv)
{
	FILE	*logs;
	FILE	*fname;
	int		fdest;
	int		c;
	char	path[100];

	if (argc != 2)
		printf("Usage: %s filename\n", argv[0]);
	
	if ((logs = fopen("./backups/.log", "w")) == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	
	log_wrapper(logs, "Starting back up: ", argv[1]);
	if ((fname = fopen(argv[1], "r")) == NULL)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	
	strcpy(path, "./backups/");
	strncat(path, argv[1], 99 - strlen(path));
	fdest = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fdest == 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}

	while ((c = fgetc(fname)) != -1)
		write(fdest, &c, 1);
	log_wrapper(logs, "Finished back up ", argv[1]);
	fclose(fname);
	close(fdest);
	return (0);
}
