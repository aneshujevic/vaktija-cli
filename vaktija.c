#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX 64

// Takes the time from Bosnian clock, checks if the time is made up from one or two digits and modifies the time accordingly
// Hours are formatted so that the : sign is it while < is sign after minutes
void get_BiH_time(char (*line)[MAX], int *hours, int *minutes)
{
	int i = 0;

	while ((*line)[i] != '\0') // (*line) is derefenced array
	{
		if (isdigit((*line)[i]) && isdigit((*line)[i + 1]) && (*line)[i + 2] == ':')
			*hours = ((*line)[i] - '0') * 10 + (*line)[++i] - '0';
		else if (isdigit((*line)[i]) && (*line)[i + 1] == ':')
			*hours = (*line)[i] - '0';

		// When minutes are found the while loop can be stopped preemptively
		if (isdigit((*line)[i]) && isdigit((*line)[i + 1]) && (*line)[i + 2] == '<')
		{
			*minutes = ((*line)[i] - '0') * 10 + (*line)[i + 1] - '0';
			break;
		}
		else if (isdigit((*line)[i]) && (*line)[i + 1] == '<')
		{
			*minutes = (*line)[i] - '0';
			break;
		}

		i++;
	}
}

// Calculates time differences between Bosnia and Novi Pazar, prayer by prayer, made to be portable for other cities too
void calculate_differences(int *hours, int *minutes, int *differences)
{
	if ((*minutes + *differences) < 0) // e.g. 18:03 + (-5) is lesser than 0 and the result should be 17:58
	{
		*minutes = *minutes + *differences + 60;
		(*hours)--;
	}
	else
	{ // else just add the differences
		*minutes += *differences;
	}
}

int main()
{
	char line[MAX], home_dir[MAX], config_dir[MAX];
	int differences[6];
	char prayers[6][14] = {"Zora", "Izlazak Sunca", "Podne", "Ikindija", "Aksam", "Jacija"};
	int no_read = 0, hours, minutes;
	FILE *config, *uname;

	if( (uname = popen("/bin/echo $HOME", "r")) == NULL)
	{
		printf("Could not find home directory.. :(\n");
		exit(EXIT_FAILURE);
	}

	fgets(home_dir, MAX, uname);
	sprintf(config_dir, "%s/vaktija/vaktija.conf", home_dir);

	//config = fopen("/home//vaktija/vaktija.conf", "r"); // Config file containing differences in time between Bosnia and the current city
	if ( (config = fopen(config_dir, "r")) == NULL)
	{
		fprintf(stderr, "Error while opening the vaktija.conf file!\n");
		exit(EXIT_FAILURE);
	}

	while (fscanf(config, "%d", &differences[no_read]) != EOF) // Read the differences into the main memory
		no_read++;

	no_read = 0;
	system("clear");
	while (no_read <= 5)
	{
		fgets(line, MAX - 1, stdin);
		if (strstr(line, "vakat-malo")) // If class for prayer time is found, extract the prayer time, calculate the difference and print it out
		{
			get_BiH_time(&line, &hours, &minutes);
			calculate_differences(&hours, &minutes, &differences[no_read]);
			printf("\n%s - %02d:%02d\n\n", prayers[no_read], hours, minutes);
			no_read++; // Increment the number of read times
		}
	}

	fclose(uname);
	fclose(config);

	exit(EXIT_SUCCESS);
}
