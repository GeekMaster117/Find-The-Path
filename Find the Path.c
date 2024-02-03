#include "ASCII Engine.h"
#include <stdbool.h>

//Use the variables below to configure the system, change the code only if you know what you are doing

//NOTE:- The value of no variable should be negative

const int path_limit = 50; //Maximum steps a test subject can take in it's lifetime, NOTE:- Array size of path of struct node, child_path of struct node and this value should be same, change both of them if needed
const int test_subjects = 50; //No.of test subjects, NOTE:- Structure array size of all_nodes and this value should be same, change both of them if needed, should be more than 0
const int max_generations = 0; //Maxminum no.of generations simulated before terminating, put 0 to have no limit on generations simulated
const int max_mutations = 2; //Maximum no.of mutations in the path of children, must be less than path_limit
const int start_x = 50; //Starting position X of all the test subjects, NOTE:- This value should be less than canvas_width
const int start_y = 12; //Starting position Y of all the test subjects, NOTE:- This value should be less than canvas_height
const int dest_x = 0; //The position X test subjects need to reach, NOTE:- This value should be less than canvas_width
const int dest_y = 0; //The position Y test subjects need to reach, NOTE:- This value should be less than canvas_height
const int canvas_width = 100; //Width of the play area of test subjects, NOTE:- This value should be greater than both start_x and dest_x
const int canvas_height = 25; //Height of the play area of test subjects, NOTE:- This value should be greater than both start_y and dest_y
const int ref_x = 99;//Reference point x for scoring
const int ref_y = 24;//Reference point y for scoring
const float simulationSpeed = 60.00; //No.of generations simulated per second
const float travelSpeed = 20.00; //No.of positions that a test subject can traverse in a second
const int displayTestSubjectsInterval = 20; //Every nth generation will be displayed
const bool displayTestSubjects = true; //Displays test subjects
const bool displayTravelling = true; //Displays the travalling path of test cases
const bool displayOnlyBest = true; //Displays only the best test subject in each generation
const bool leaveTrail = true; //Displays the path followed by test subjects in each generation

//--------------------------------------------------------------------------------------------------------------------------------------

canvas c;
clock_t travelClock;
float travelTime;

struct node
{
	int path[50];
	int child_path[50];
	int score;
	int x,y;
	int parent;
}all_nodes[50];

int best;

void initialise()
{
	int i,j;
	travelClock = clock();
	travelTime = (float)1/travelSpeed;
	srand(time(0));
	for(i = 0;i < test_subjects;i++)
	{
		for(j = 0;j < path_limit;j++)
		all_nodes[i].path[j] = rand() % 8;
		all_nodes[i].x = start_x;
		all_nodes[i].y = start_y;	
	}
	initialise_ascii_engine();
	initialise_canvas(&c);
	set_canvas_dimensions(&c,canvas_width,canvas_height);
}

int dist(int x1,int y1,int x2,int y2)
{
	return (int)sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
}

void display_nodes()
{
	int i;
	if(!leaveTrail) clear_canvas(&c);
	if(displayOnlyBest) insert_char(&c, '*', all_nodes[best].x, all_nodes[best].y);
	else for(i = 0;i < test_subjects;i++) insert_char(&c, '*', all_nodes[i].x, all_nodes[i].y);
}
bool printbool = false;

void traverse(int generation)
{
	int i, j;
	clear_canvas(&c);
	for(j = 0;j < path_limit;j++)
	{
		for(i = 0;i < test_subjects;i++)
		{
			switch(all_nodes[i].path[j])
			{
				case 0: if(all_nodes[i].x > 0 && all_nodes[i].y > 0)
						{
							all_nodes[i].x -= 1;
							all_nodes[i].y -= 1;
						}
					break;
				case 1: if(all_nodes[i].y > 0) all_nodes[i].y -= 1;
					break;
				case 2: if(all_nodes[i].x < canvas_width - 1 && all_nodes[i].y > 0)
						{
							all_nodes[i].x += 1;
							all_nodes[i].y -= 1;
						}
					break;
				case 3: if(all_nodes[i].x < canvas_width - 1) all_nodes[i].x += 1;
					break;
				case 4: if(all_nodes[i].x < canvas_width - 1 && all_nodes[i].y < canvas_height - 1)
						{
							all_nodes[i].x += 1;
							all_nodes[i].y += 1;	
						}
					break;
				case 5: if(all_nodes[i].y < canvas_height - 1) all_nodes[i].y += 1;
					break;
				case 6: if(all_nodes[i].x > 0 && all_nodes[i].y < canvas_height - 1)
						{
							all_nodes[i].x -= 1;
							all_nodes[i].y += 1;	
						}
					break;
				case 7: if(all_nodes[i].x > 0) all_nodes[i].x -= 1;
					break;
			}
		}
		display_nodes();
		if(displayTestSubjects && displayTravelling && (generation % displayTestSubjectsInterval == 0 || generation == 1))
		{
			while(((double)clock())/CLOCKS_PER_SEC < ((double)travelClock)/CLOCKS_PER_SEC + travelTime);
			travelClock = clock();
			refresh(&c);
			printf("\ngeneration: %d", generation);
		}
	}
	if(displayTestSubjects && (generation % displayTestSubjectsInterval == 0 || generation == 1))
	{
		while(((double)clock())/CLOCKS_PER_SEC < ((double)travelClock)/CLOCKS_PER_SEC + travelTime);
		travelClock = clock();
		refresh(&c);
		printf("\ngeneration: %d", generation);
	}
}

void generate_score()
{
	int i,node_to_dest,dest_to_ref, min_score = 2147483647;
	dest_to_ref = dist(dest_x,dest_y,ref_x,ref_y);
	for(i = 0;i < test_subjects;i++)
	{
		node_to_dest = dist(all_nodes[i].x,all_nodes[i].y,dest_x,dest_y);
		all_nodes[i].score = dest_to_ref - node_to_dest;
		if(all_nodes[i].score < min_score) min_score = all_nodes[i].score;
	}
	for(i = 0;i < test_subjects;i++) all_nodes[i].score -= min_score;
	best = 0;
	for(i = 1;i < test_subjects;i++)if(all_nodes[i].score > all_nodes[best].score)best = i;
}

void find_parent()
{
	int i,j,begin[test_subjects],end[test_subjects],rand_int;
	begin[0] = 0;
	end[0] = all_nodes[0].score;
	for(i = 1;i < test_subjects;i++)
	{
		begin[i] = end[i - 1] + 1;
		end[i] = begin[i] + all_nodes[i].score;
	}
	for(i = 0;i < test_subjects;i++)
	{
		if(i == best)
		{
			all_nodes[i].parent = i;
			continue;
		}
		rand_int = (int)rand() % (end[49] + 1);
		j = 0;
		while(!(rand_int >= begin[j] && rand_int <= end[j]))j++;
		all_nodes[i].parent = j;
	}
}

void generate_children()
{
	int i, j, k, rand_int_1, rand_int_2;
	for(i = 0;i < test_subjects;i++)
	{
		for(j = 0;j < path_limit;j++) all_nodes[i].child_path[j] = all_nodes[all_nodes[i].parent].path[j];
		if(i == best) continue;
		for(k = 0;k < max_mutations;k++)
		{
			rand_int_1 = rand() % 8;
			rand_int_2 = rand() % path_limit;
			all_nodes[i].child_path[rand_int_2] = rand_int_1;
		}
	}
	for(i = 0;i < test_subjects;i++) for(j = 0;j < path_limit;j++) all_nodes[i].path[j] = all_nodes[i].child_path[j];
}

void reset_position()
{
	int i;
	for(i = 0;i < test_subjects;i++)
	{
		all_nodes[i].x = start_x;
		all_nodes[i].y = start_y;
	}
}
bool check_victory(int generation)
{
	int i;
	for(i = 0;i < test_subjects;i++) if(all_nodes[i].x == dest_x && all_nodes[i].y == dest_y)
	{
		if(displayTestSubjects) refresh(&c);
		printf("\ngeneration: %d program: %d\n",generation,i);
		return true;
	}
	return false;
}

int main()
{
	initialise();
	clock_t simClock = clock();
	float simTime = (float)1/simulationSpeed;
	int generation = 1;
	if(max_generations == 0)
		for(;!check_victory(generation);generation++)
		{
			while(((double)clock())/CLOCKS_PER_SEC < ((double)simClock)/CLOCKS_PER_SEC + simTime);
			simClock = clock();
			reset_position();
			traverse(generation);
			generate_score();
			find_parent();
			generate_children();
		}
	else
	{
		for(;generation <= max_generations;generation++)
		{
			while(((double)clock())/CLOCKS_PER_SEC < ((double)simClock)/CLOCKS_PER_SEC + simTime);
			simClock = clock();
			if(check_victory(generation))
			{
				getch();
				return 1;
			}
			reset_position();
			traverse(generation);
			generate_score();
			find_parent();
			generate_children();
		}
		clear_display();
		printf("Program terminated, test cases failed to reach destination before maximum generations limit");
	}
	getch();
	return 0;
}