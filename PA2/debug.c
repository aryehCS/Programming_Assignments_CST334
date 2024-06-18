#include "src/student_code.h"

#include "unistd.h"
#include <sys/syscall.h>
#include <stdio.h>

int main() {
  const char msg[] = "Hello World!\n";
  write(STDOUT_FILENO, msg, sizeof(msg)-1);
  syscall(SYS_write, STDOUT_FILENO, msg, sizeof(msg)-1);

  char buff[1024];
  syscall(SYS_read, STDIN_FILENO, buff, 5);
  printf("%s\n", buff);
  return 0;


        SCHEDULER_STATS* s = get_empty_stats_block();
        PROCESS *p = create_process(1.0f, 0, 0.0f);
        p->time_remaining = 0; // Pretend the job ran
        mark_process_end(s, p, 1.0f, 0.0f);

        printf("%d\n", (p->length == 1.0f));
        printf("%d\n", (p->priority == 0));
        printf("%d\n", (p->entry_time == 0.0f));
        printf("%d\n", (p->time_remaining == 0.0f));

        printf("%d\n", (s->num_processes_started == 0));
        printf("%d\n", (s->num_processes_completed == 1));
        printf("%d\n", (s->sum_of_turnaround_times == 1.0f));
        printf("%d\n", (s->sum_of_response_time == 0.0f));
        printf("%d\n", (s->average_turnaround_time == 0.0f));
        printf("%d\n", (s->average_response_time == 0.0f));
        printf("%d\n", (s->completion_time == 0.0f));


}
