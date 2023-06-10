// implement the functions in schedule.h
#include "schedule.h"
#include "linuxlist.h"
#include <stdlib.h>

int add_job( struct list_head *pJobList , sJob *pJob ) {
    if (!pJobList || !pJob) {
        return -1;
    }

    list_add(&(pJob->list), pJobList);
}

int schedule( struct list_head *pJobList , struct list_head *pSchedJobList ) {
    if (!pJobList || !pSchedJobList) {
        return -1;
    }

    int last_arrival = -1, end = 0, check = 1;
    // loop until all jobs are scheduled
    while (check) {
        int arrival = 1 << 30;
        // find the next job to schedule
        struct list_head *pJob;
        // temp variable to store the min arrival job
        sJob *p = NULL;
        list_for_each(pJob, pJobList) {
            // get the entry of the job
            sJob *pEntry;
            list_entry(pJob, sJob, list);
            // get and find the min arrival time of the job
            // then record the arrival time and the job
            if (pEntry->arrival < arrival && pEntry->arrival > last_arrival) {
                arrival = pEntry->arrival;
                p = pEntry;
            }
        }

        // schedule the job
        if (p) {
            // update the last arrival time
            last_arrival = p->arrival;
            // set start time
            int start = (end > p->arrival) ? end : p->arrival;
            // update the end time
            end += start + p->duration;
            // create the scheduled job
            sSchedJob *pSchedJob = (sSchedJob *)malloc(sizeof(sSchedJob));
            pSchedJob->id = p->id;
            pSchedJob->start = start;
            pSchedJob->stop = end;
            // add the scheduled job to the tail of the list
            list_add_tail(&(pSchedJob->list), pSchedJobList);
        }
        else {
            check = 0;
        }
    }

    // exit
    return 0;
}