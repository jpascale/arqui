#include <shell.h>
#include <time.h>

int shell_buffer_parser(tCommand * command, char * bff, int bff_len)
{
	char * p;
	int dispatcher = 0;
	int struct_index[3] = {0, 0, 0};

	if (bff[0] == 0 || bff[0] == ' ')
		return -1;

	for (int i = 0; i < bff_len; i++)
	{
		if (dispatcher > 2)
			return -1;

		if (bff[i] == '\n'){
			return dispatcher;
		}

		if (bff[i] == ' ')
		{
			dispatcher++;
		}
		else
		{
			switch (dispatcher){
				case 0:
					p = command->primary; 
					break;

				case 1:
					p = command->secondary;
					break;

				case 2:
					p = command->args;
					break;
			}

			p[struct_index[dispatcher]] = bff[i];
			struct_index[dispatcher]++;
			p[struct_index[dispatcher]] = 0;
		}

		if (struct_index[dispatcher] > MAX_PARAMS_LEN)
			return -1;

	}

	return dispatcher;
}

int shell_command_execute(tCommand * command)
{
	char * primary = command->primary;

	if (strcmp("time", primary) == 0)
	{
		shell_print_time();
	}
	else
	{
		return -1;
	}
}

void shell_print_time(void)
{
	int v_time[] = {get_time(HOUR), get_time(HOUR), get_time(SECONDS)};

	for (int i = 0; i < 3; i++){
		
		if (v_time[i] < 10)
			putchar('0');

		printint(v_time[i]);

		if (i != 2)
			putchar(':');
	}

	putchar('\n');
}