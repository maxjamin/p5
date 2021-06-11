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

	int arrive_time;
	int end_time;
	int time_left;
	int first_started;

	int process_timer;
	int waiting_time;

} Process;

typedef struct input_parameter
{
	int buffer[size_of_buffer];
	int size_of_input;

} input_parameter;

int st_for_fc_fs;
int time_quantum_parameter;

void copy_process_list(Process *List_of_process
							, Process *list
							, int size_of_process_list)
{
	int i = 0;
	while(i < size_of_process_list)
	{
		memcpy(&list[i], &List_of_process[i], sizeof(List_of_process[i]));
		i++;
	}
}

int find_averages(  Process *list_of_process
				  , int size_of_process_list)
{
	double av_resp = 0;
	double av_ta = 0;
	double av_wait = 0;

	int i =0;
	while(i < size_of_process_list)
	{
		/*printf("end: %d Arrive: %d durration: %d\n"
		, list_of_process[i].end_time
		, list_of_process[i].arrive_time
		, list_of_process[i].durration_of_process); */

		av_resp += (float) list_of_process[i].arrive_time - list_of_process[i].arrival_time;
		av_ta += (float) list_of_process[i].end_time - list_of_process[i].arrival_time;
		av_wait += (float) (list_of_process[i].end_time - list_of_process[i].arrival_time) - list_of_process[i].durration_of_process;
		i++;
	}

	printf( "Avg. Resp.:%.2f", (double) (av_resp / size_of_process_list));
	printf(", Avg. T.A.:%.2f", (double) (av_ta / size_of_process_list));
	printf(", Avg. Wait:%.2f\n\n", ( double) (av_wait / size_of_process_list));
}

int first_come_first_served(  Process *list_of_process
						  	, int size_of_process_list)
{

	//starting clock for the algorithm
	st_for_fc_fs = 0; 

	int inc_processes = 0;
	while(inc_processes < size_of_process_list)
	{

		if(st_for_fc_fs >= list_of_process[inc_processes].arrival_time  )
		{
			list_of_process[inc_processes].arrive_time = st_for_fc_fs;
			/*printf("Starting process %d at %d %d, arrival: %d Durration: %d\n", inc_processes, st_for_fc_fs
				,list_of_process[inc_processes].arrive_time + list_of_process[inc_processes].durration_of_process
				,list_of_process[inc_processes].arrival_time
				,list_of_process[inc_processes].durration_of_process);*/	

			//if process is finished move to the next one
			while(( list_of_process[inc_processes].arrive_time + list_of_process[inc_processes].durration_of_process) 
				> st_for_fc_fs)
				st_for_fc_fs++;

			list_of_process[inc_processes].end_time = st_for_fc_fs;
			inc_processes++;
		}	
		else
			st_for_fc_fs++;
	}

	find_averages(list_of_process, size_of_process_list);
}

int shortest_job_first_algorithm(  Process *list_of_process
						  	, int size_of_process_list)
{
	printf("Starting shortest_job_first_algorithm\n");
	//starting clock for the algorithm
		//starting clock for the algorithm
	st_for_fc_fs = 0; 

	int inc_processes = 0;
	while(inc_processes < size_of_process_list)
	{
		//find the process with the shortest length
		int inc_shortest_burst = 0;
		int inc_of_shortest_burst = 0;
		int shortest_burst_size = 99999;
		int process_ready = 0;

		while(inc_shortest_burst < size_of_process_list)
		{
			//printf("Size is: %d\n", list_of_process[inc_shortest_burst].time_left);
			if( list_of_process[inc_shortest_burst].time_left < shortest_burst_size &&
				list_of_process[inc_shortest_burst].time_left != 0 &&
				list_of_process[inc_shortest_burst].arrival_time <= st_for_fc_fs )
			{
				inc_of_shortest_burst = inc_shortest_burst;
				shortest_burst_size = list_of_process[inc_of_shortest_burst].time_left;
				process_ready = 1;
			}
			inc_shortest_burst++;
		}
		/*printf("Shortest is %d Time: %d\n", list_of_process[inc_of_shortest_burst].durration_of_process
										  , st_for_fc_fs); */

		//start process
		if(process_ready)
		{
			if(list_of_process[inc_of_shortest_burst].first_started == 0)
			{
				list_of_process[inc_of_shortest_burst].arrive_time = st_for_fc_fs;
				list_of_process[inc_of_shortest_burst].first_started = 1;
			}

			/*printf("Starting process %d at %d %d, arrival: %d time: %d\n", inc_of_shortest_burst, st_for_fc_fs
				,list_of_process[inc_of_shortest_burst].arrive_time + list_of_process[inc_of_shortest_burst].durration_of_process
				,list_of_process[inc_of_shortest_burst].arrival_time
				,list_of_process[inc_of_shortest_burst].time_left);		*/	

			//wait for process to go one cycle
			while(list_of_process[inc_of_shortest_burst].time_left > 0)
			{
					list_of_process[inc_of_shortest_burst].time_left--;
					st_for_fc_fs++;
			}

			//now if process has completed its desired time
			if(list_of_process[inc_of_shortest_burst].time_left == 0)
			{
				list_of_process[inc_of_shortest_burst].end_time = st_for_fc_fs;
				inc_processes++;
			}
			
		}
		else
			st_for_fc_fs++;
	}
	find_averages(list_of_process, size_of_process_list);

}

int shortest_Remaining_algorithm(Process *list_of_process
						  	, int size_of_process_list)
{
	printf("Starting shortest_Remaining_algorithm\n");
	//starting clock for the algorithm
	st_for_fc_fs = 0; 

	int inc_processes = 0;
	while(inc_processes < size_of_process_list)
	{

		//find the process with the shortest length
		int inc_shortest_burst = 0;
		int inc_of_shortest_burst = 0;
		int shortest_burst_size = 99999;
		int process_ready = 0;

		while(inc_shortest_burst < size_of_process_list)
		{
			//printf("Size is: %d\n", list_of_process[inc_shortest_burst].time_left);
			if( list_of_process[inc_shortest_burst].time_left < shortest_burst_size &&
				list_of_process[inc_shortest_burst].time_left != 0 &&
				list_of_process[inc_shortest_burst].arrival_time <= st_for_fc_fs )
			{
				inc_of_shortest_burst = inc_shortest_burst;
				shortest_burst_size = list_of_process[inc_of_shortest_burst].time_left;
				process_ready = 1;
			}
			inc_shortest_burst++;
		}
		/*printf("Shortest is %d Time: %d\n", list_of_process[inc_of_shortest_burst].durration_of_process
										  , st_for_fc_fs); */

		//start process
		if(process_ready)
		{
			if(list_of_process[inc_of_shortest_burst].first_started == 0)
			{
				list_of_process[inc_of_shortest_burst].arrive_time = st_for_fc_fs;
				list_of_process[inc_of_shortest_burst].first_started = 1;
			}

			/*printf("Starting process %d at %d %d, arrival: %d Durration: %d\n", inc_processes, st_for_fc_fs
				,list_of_process[inc_processes].arrive_time + list_of_process[inc_processes].durration_of_process
				,list_of_process[inc_processes].arrival_time
				,list_of_process[inc_processes].durration_of_process);	*/		

			//wait for process to go one cycle
			list_of_process[inc_of_shortest_burst].time_left--;
			
			//now if process has completed its desired time
			if(list_of_process[inc_of_shortest_burst].time_left == 0)
			{
				list_of_process[inc_of_shortest_burst].end_time = st_for_fc_fs;
				inc_processes++;
			}
			
		}
		
		st_for_fc_fs++;

	}

	find_averages(list_of_process, size_of_process_list);

}
int check_list_for_value(Process * list_of_process, int inc_list, int size_of_process_list)
{
	for (int i = 0; i < size_of_process_list; ++i)
	{
		if(list_of_process[i].arrival_time == list_of_process[inc_list].arrival_time)
			return 1;
	}
	return 0;
}

int find_inc_in_list(Process * list_of_process, int arrival_time, int size_of_process_list)
{
	for (int i = 0; i < size_of_process_list; ++i)
	{
		if(list_of_process[i].arrival_time == arrival_time)
			return i;
	}
	return 0;
}

int round_robin_algorithm(Process *list_of_process
						  	, int size_of_process_list)
{
	printf("Round Rboin with Time Quantum of %d\n", time_quantum_parameter);
	//starting clock for the algorithm
	st_for_fc_fs = 0; 

	Process queue_processes[100];
	int inc_queu_proc = 0;

	int inc_list = 0;
	int start_of_queue = 0;
	int j;

	st_for_fc_fs = 0; 

	int inc_processes = 0;
	while(inc_processes < size_of_process_list)
	{
		//add processes that are <= Time
		inc_list = start_of_queue;
		while(inc_list < size_of_process_list)
		{
			//make sure that the processes is not already on the list
			if(list_of_process[inc_list].arrival_time <= st_for_fc_fs 
				&& check_list_for_value(list_of_process, inc_list, size_of_process_list))
			{

				j = inc_queu_proc;
				while(j > 0)
				{
					queue_processes[j] = queue_processes[j-1];
					j--;
				}
				queue_processes[0] = list_of_process[inc_list];

				/*printf("Added process %d Time % d start: %d end: %d\n", queue_processes[0].arrival_time
					, st_for_fc_fs
					, start_of_queue
					, inc_queu_proc);*/

				inc_queu_proc++;
				start_of_queue++;	
			}
			inc_list++;
		}

		//iterate through processes in queue
		if(!inc_queu_proc)
			st_for_fc_fs++;
		else
		{
			for(int inc_through_list = 0; inc_through_list < inc_queu_proc;)
			{

				/*for(int inc_through = 0; inc_through < inc_queu_proc; inc_through++)
				{
					printf("queue proc[%d]: %d %d Time %d, Time left %d\n"
						, inc_through
						, queue_processes[inc_through].arrival_time
						, queue_processes[inc_through].durration_of_process
						, st_for_fc_fs
						, queue_processes[inc_through].time_left);
				}
				printf("\n");*/

				if(queue_processes[inc_through_list].first_started == 0)
				{
					int i = find_inc_in_list(list_of_process
						, queue_processes[inc_through_list].arrival_time
						, size_of_process_list);

					list_of_process[i].arrive_time = st_for_fc_fs;
					list_of_process[i].first_started = 1;
				}


				//if time_left is small or equal to time quantum, remove from queue
				if(queue_processes[inc_through_list].time_left <= time_quantum_parameter) 
				{

					st_for_fc_fs += queue_processes[inc_through_list].time_left;
					queue_processes[inc_through_list].time_left = 0;

					//find end time
					int i = find_inc_in_list(list_of_process
						, queue_processes[inc_through_list].arrival_time
						, size_of_process_list);

					list_of_process[i].end_time = st_for_fc_fs;

					/*printf("removed process1[%d] %d\n"
						, inc_through_list
						, queue_processes[inc_through_list].arrival_time);*/

					//remove and shift all queue over left
					Process temp;
					temp.durration_of_process = 0;
					j = inc_through_list;
					while(j < inc_queu_proc-1)
					{
						queue_processes[j] = queue_processes[j+1];
						++j;
					}
					queue_processes[inc_queu_proc-1] = temp;

					inc_queu_proc--; //shorten queue
					inc_processes++; //tell loop 1 less process
				}
				else // if larger time then quantum, move object to end
				{
					queue_processes[inc_through_list].time_left -= time_quantum_parameter;
					st_for_fc_fs += time_quantum_parameter;

					//waiting time
					if(queue_processes[inc_through_list].first_started)
					{
						queue_processes[inc_through_list].waiting_time = st_for_fc_fs - 
						queue_processes[inc_through_list].durration_of_process;
					}

					//move to end
					Process temp = queue_processes[inc_through_list];
					j = inc_through_list;
					while(j < inc_queu_proc-1)
					{
						queue_processes[j] = queue_processes[j+1];
						++j;
					}
					queue_processes[inc_queu_proc-1] = temp;
					inc_through_list++;
				}

			}
		}
		//st_for_fc_fs++;

	}

	find_averages(list_of_process, size_of_process_list);
}

int add_inputs_to_process_list(input_parameter input , Process *List_of_process )
{
	int j = 0;
	int incr_in_proc = 0;
	while(j < input.size_of_input)
	{
		List_of_process[incr_in_proc].arrival_time = input.buffer[j];
		List_of_process[incr_in_proc].durration_of_process = input.buffer[j+1];
		List_of_process[incr_in_proc].time_left = List_of_process[incr_in_proc].durration_of_process;
		List_of_process[incr_in_proc].first_started = 0;
		List_of_process[incr_in_proc].waiting_time = 0;

		//move to new process
		j = j+2;
		incr_in_proc++;
	} 

	/*	int y = 0;
	while(y < input.size_of_input/2)
	{
		printf("Arrival: %d durration: %d\n"
			, List_of_process[y].arrival_time
			, List_of_process[y].durration_of_process);
		y++;
	}*/
}

int main(int argc, char *argv[])
{

	input_parameter Input;
	Input.size_of_input = 0;

	if(argc < 2)
	{
		printf("Error no time time_quantum_parameter specified using default 100ms\n");
		time_quantum_parameter = 100;
	}
	else
		time_quantum_parameter = atoi(argv[1]);

	int buffer[size_of_buffer];
	int j = 0;
	while(fscanf(stdin
				, "%d"
				, &Input.buffer[j]) == 1)
	{
		j++;
	}	
	Input.size_of_input = j;

	Process * list_of_process;
	int size_of_process_list = j/2;

	list_of_process = calloc(1, sizeof(Process)*j);
	add_inputs_to_process_list(Input, list_of_process);


	Process *list = calloc(1, sizeof(Process)*size_of_process_list);
	Process *list1 = calloc(1, sizeof(Process)*size_of_process_list);
	Process *list2 = calloc(1, sizeof(Process)*size_of_process_list);
	Process *list3 = calloc(1, sizeof(Process)*size_of_process_list);

	copy_process_list(list_of_process, list, size_of_process_list);
	copy_process_list(list_of_process, list1, size_of_process_list);
	copy_process_list(list_of_process, list2, size_of_process_list);
	copy_process_list(list_of_process, list3, size_of_process_list);

	first_come_first_served(list, size_of_process_list);

	shortest_job_first_algorithm(list1, size_of_process_list);

	shortest_Remaining_algorithm(list2, size_of_process_list);

	round_robin_algorithm(list3, size_of_process_list);

	free(list_of_process);
}