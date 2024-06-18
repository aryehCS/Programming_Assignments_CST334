/**
 * Aryeh Freud
 * PA2 - CST 334
 * March 12, 2024
*/
//#include <printf.h>
//#include <stdio.h>
#include "student_code.h"


void finalize_stats(SCHEDULER_STATS* stats) {
    // todo

    /**
     * No code needed here.
     * Stats are updated in the mark_process_xxx functions
     */
}


void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    // todo

    stats -> num_processes_started++; // increment the number of processes started
    //p->process_state = PROC_READY;
    //stats -> sum_of_response_time += curr_time - p -> entry_time; // add the response time to the sum of response times
}

void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    // todo

    if(p->process_state == PROC_READY){
        float response_time = curr_time - p->entry_time;
        stats ->sum_of_response_time += response_time;
        stats -> average_response_time = stats->num_processes_started == 0 ? 0 : stats->sum_of_response_time/stats->num_processes_started;
        p->process_state = PROC_RUNNING;
    }
    //fprintf(stderr, "Process: %d has this amount time remaining: %f",p->id,p->time_remaining);
    p -> time_remaining = (p -> time_remaining >= time_slice) ? p -> time_remaining - time_slice : 0.0f;
}

void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float end_time, float time_slice_remaining) {
    // todo

    stats -> num_processes_completed++; // increment the number of processes completed
    float turnaround_time = end_time - p -> entry_time; // calculate the turnaround time
        // fprintf(stderr, "%f turnAround_Time", end_time);
    stats -> sum_of_turnaround_times += turnaround_time; // add the turnaround time to the sum of turnaround times
//    if (stats -> num_processes_completed == stats -> num_processes_started) {
//        stats -> completion_time = end_time; // set the completion time to the end time
//    }
    stats ->average_turnaround_time = stats->num_processes_started == 0 ? 0 : stats->sum_of_turnaround_times/stats->num_processes_completed;
    //stats->completion_time += end_time - p->length +time_slice_remaining; //Will change later
    //delete_process(p); // delete the process
}

int compare_priority(PROCESS p1, PROCESS p2) {
    return (int)p1.priority - (int)p2.priority;

}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
    //TODO
    PROCESS *p;
    p = get_minimum(pl, compare_priority);
    return p;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
    //PROCESS *p = get_next(pl);
    // todo
    //return p;

    if (is_empty(pl)) {
        return NULL;
    }
//    if(pl->last_used == -1){
//        printf("This should print 3 times");
//        return pl->processes[0];
//    }
//    if(get_last_used(pl)->time_remaining <= 0){
//        remove_process(pl, get_last_used(pl));
//    }
    int minimum = -1;
    for(int i = 0; i < pl ->num_processes; i++){
        if(minimum < 0){
            minimum = 0;
        }
        else if(pl->processes[i]->entry_time < pl->processes[minimum]->entry_time){
            minimum = i;
        }
    }
    return pl->processes[minimum];
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
    //PROCESS* p;
    // todo
    if (is_empty(pl)) {
        return NULL;
    }
    PROCESS* next_process = get_next(pl);

    return next_process;

    //return get_next(pl);
}
int stcf_time_compare(PROCESS p1, PROCESS p2) { // helper function
    if (p1.time_remaining < p2.time_remaining) {
        return -1;
    } else if (p1.time_remaining > p2.time_remaining) {
        return 1;
    } else {
        return 0;
    }
}


PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
    //PROCESS* p;
    // todo
    if (is_empty(pl)) {
        return NULL;
    }
//    if(pl->last_used == -1){
//        printf("This should print 3 times");
//        return pl->processes[0];
//    }
//    if(get_last_used(pl)->time_remaining <= 0){
//        remove_process(pl, get_last_used(pl));
//    }
    int minimum = -1;
    for(int i = 0; i < pl ->num_processes; i++){
        if(minimum < 0){
            minimum = 0;
        }
        else if(pl->processes[i]->length < pl->processes[minimum]->length){
            minimum = i;
        }
    }
    return pl->processes[minimum];
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
    //PROCESS* p;
    // todo

    if (is_empty(pl)) {
        return NULL;
    }

    int maximum = -1;
    for(int i = 0; i < pl ->num_processes; i++){
        if(maximum < 0){
            maximum = 0;
        }
        else if(pl->processes[i]->entry_time > pl->processes[maximum]->entry_time){
            maximum = i;
        }
    }
    return pl->processes[maximum];
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
    //PROCESS *p;
    // todo

    if (is_empty(pl)) {
        return NULL;
    }
    return get_minimum(pl, stcf_time_compare);
}
