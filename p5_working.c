#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <time.h>

/* Created by: Ben Smith
 * Class: CS3060 X01 summer 2021 B1
 * Assignment: Project 4
 */

#define size_of_buffer 50

typedef struct process
{
	int arrival_time;
	int durration_of_process;

	clock_t response_time;
	clock_t turn_around_time;
	clock_t wait_time;

} Process;

typedef struct input_parameter
{
	int buffer[size_of_buffer];
	int size_of_input;
	int time_quantum_parameter;

} input_parameter;


int first_come_first_served(const Process *List_of_process )
{
	1 2 3

}

int round_robin_algorithm()
{

}

int shortest_job_first_algorithm()
{
	
}

int shortest_Remaining_algorithm()
{
	
}

int add_inputs_to_process_list(input_parameter input , Process *List_of_process )
{
	int j = 0;
	int incr_in_proc = 0;
	while(j < input.size_of_input)
	{
		List_of_process[incr_in_proc].arrival_time = input.buffer[j];
		List_of_process[incr_in_proc].durration_of_process = input.buffer[j+1];

		//move to new process
		j = j+2;
		incr_in_proc++;
	}

	/*	int y = 0;
	while(y < Input.size_of_input/2)
	{
		printf("Arrival: %d durration: %d\n"
			, List_of_process[y].arrival_time
			, List_of_process[y].durration_of_process);
		y++;
	}*/
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Error no commands specified\n");
		return -1;
	}

	input_parameter Input;
	Input.size_of_input = 0;
	Input.time_quantum_parameter = 0;

	int buffer[size_of_buffer];
	int j = 0;
	while(fscanf(stdin
				, "%d"
				, &Input.buffer[j]) == 1)
	{
		j++;
	}	
	Input.size_of_input = j;

	Input.time_quantum_parameter = atoi(argv[1]);
	Process * list_of_process;
	int size_of_process_list = j/2;

	list_of_process = calloc(1, sizeof(Process)*j);
	add_inputs_to_process_list(Input, list_of_process);


	first_come_first_served(list_of_process);



	free(list_of_process);
}