#include "dynamic_queue.h"
#include <time.h>
int simulation();
int main()
{
    srand(time(NULL));
    if(!simulation()){
        puts("ERROR");
        return 1;
    }
    return 0;
}

int simulation()
{

    tQueue q;
    initializeQueue(&q);
    int cashTimes[]= {1,3,5}, arrivalTimes[]= {1,5,9};
    int arrival_Time=0, cash_time=0,people_served =0, times_empty =0, total_time=0, elapsed_time, processing_time;

    puts("---------ATM SIMULATION---------");

    total_time += arrivalTimes[rand()%3];
    processing_time = cashTimes[rand()%3];
    Enqueue(&q,&processing_time,sizeof(processing_time));

    arrival_Time = arrivalTimes[rand()%3];

    peek(&q, &cash_time,sizeof(cash_time));
    while(times_empty<5)
    {

        elapsed_time = MIN(cash_time, arrival_Time);

        cash_time-= elapsed_time;
        arrival_Time -= elapsed_time;
        total_time+= elapsed_time;

        if(!cash_time)
        {
            people_served++;
            Dequeue(&q,&processing_time,sizeof(processing_time));

            if(isEmpty(&q) && arrival_Time>0)
            {
                elapsed_time+=arrival_Time;
                arrival_Time=0;
                times_empty++;
            }
            else if (!isEmpty(&q))
            {
                peek(&q, &cash_time,sizeof(cash_time));
            }



        }

        if(!arrival_Time)
        {
            processing_time = cashTimes[rand()%3];
            Enqueue(&q,&processing_time,sizeof(processing_time));


            arrival_Time = arrivalTimes[rand()%3];

            if(!cash_time)
            {
                peek(&q, &cash_time,sizeof(cash_time));
            }

        }
    }

    printf("Served people: %d, total simulation time: %d minutes.\n", people_served, total_time);

    return 1;
}
