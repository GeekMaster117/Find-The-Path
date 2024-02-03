Find The Path
--------------------------------------------------------------------------------------------
HOW TO USE:-

-> Compile the source code to the target machine and run the compiled file.
--------------------------------------------------------------------------------------------
HOW IT WORKS:-

-> The goal of the program is to run a simulation where some 'test subjects' have to find their way from a position to another.

-> At the beginning, the 'test subjects' don't know how to reach the target position, using genetic algorithm they learn to get close to the target postition with each generation.

-> The simulation terminates itself when any of the 'test subject' reaches the target position or when none of them are able to reach the target position by specific generation.

-> The genes of the 'test subjects' here are an array of integers containing any digit from 0 to 7, where the digit specifies which direction should the 'test subject' head towards.

--------------------------------------------------------------------------------------------
HOW TO CONFIGURE:-

The source code contains some global variables with default values which can be used to customise the simulation.

-> path_limit - Maximum steps a test subject can take in it's lifetime, NOTE:- Array size of path of struct node, child_path of struct node and this value should be same, change both of them if needed

-> test_subjects - No.of test subjects, NOTE:- Structure array size of all_nodes and this value should be same, change both of them if needed, should be more than 0

-> max_generations - Maxminum no.of generations simulated before terminating, put 0 to have no limit on generations simulated

-> max_mutations - Maximum no.of mutations in the path of children, must be less than path_limit

-> start_x - Starting position X of all the test subjects, NOTE:- This value should be less than canvas_width

-> start_y - Starting position Y of all the test subjects, NOTE:- This value should be less than canvas_height

-> dest_x - The position X test subjects need to reach, NOTE:- This value should be less than canvas_width

-> dest_y - The position Y test subjects need to reach, NOTE:- This value should be less than canvas_height

-> canvas_width - Width of the play area of test subjects, NOTE:- This value should be greater than both start_x and dest_x

-> canvas_height - Height of the play area of test subjects, NOTE:- This value should be greater than both start_y and dest_y

-> ref_x - Reference point x for scoring

-> ref_y - Reference point y for scoring

-> simulationSpeed - No.of generations simulated per second

-> travelSpeed - No.of positions that a test subject can traverse in a second

-> displayTestSubjectsInterval - Every nth generation will be displayed

-> displayTestSubjects - Displays test subjects

-> displayTravelling - Displays the travalling path of test cases

-> displayOnlyBest - Displays only the best test subject in each generation

-> leaveTrail - Displays the path followed by test subjects in each generation
-------------------------------------------------------------------------------------------
