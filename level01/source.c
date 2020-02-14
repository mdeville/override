#include <stdio.h>
#include <string.h>

char username[256];

int	verify_user_name(void)
{
	puts("verifying username....\n");
	return (strcmp(username, "dat_wil"));
}

int verify_user_pass(char *input)
{
	return (strcmp(input, "admin"));
}

int	main(void)
{
	char	pass[64];
	int		ret;

	puts("********* ADMIN LOGIN PROMPT *********");
	
	printf("Enter Username: ");
	fgets(username, 256, stdin);
	if (verify_user_name() != 0)
	{
		puts("nope, incorrect username...\n");
		return (1);
	}

	puts("Enter Password: ");
	fgets(pass, 100, stdin);
	ret = verify_user_pass(pass);
	if (!ret || ret)
	{
		puts("nope, incorrect password...\n");
		return (1);
	}
	return (0);
}
