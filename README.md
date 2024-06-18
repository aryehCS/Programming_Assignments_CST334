Your task

Your job is to:

Write the metrics gathering and calculating functions. I have a few of these written to track the progress of jobs and calculate our metrics at the end but I've left it up to you to figure out how to implement them.
Fix my priority scheduler implementation. We didn't talk about priority scheduling directly in class but the idea is that the job with the highest priority should be scheduled first, regardless of when it came in or what other jobs there are -- it's very closely related to MLFQ scheduling.
Write a few more scheduling algorithms. To do this you'll have to look at what functions are available to you, and very possibly write a few more! (You will likely be adding a few extra functions of your own to student_code.c and student_code.h for this assignment!)
Functions you'll be writing

// Write metric tracking code (35 points total)
void finalize_stats(SCHEDULER_STATS* stats); // 15 points
void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started); // 10 points
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed); // 10 points

// Fix this for 15 points
PROCESS* priority_process_selector(PROCESS_LIST* pl); // 15 points

// Implement these for 30 points
PROCESS* fifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* rr_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* sjf_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* lifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* stcf_process_selector(PROCESS_LIST* pl); // 6 points
