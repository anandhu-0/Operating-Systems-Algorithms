# OPERATING SYSTEM ALGORITHMS

The project include OS CPU scheduling algorithms.The goal is to understand the logic behind cpu scheduling  algorithms and process allocation and implementation.


## The Algorithms Included


### Scheduling

 1.first come first serve (fcfs)
 2.shortest job first (sjf)
 3.round robin(rr)
 4.shortest remaining time first(srtf)


## how to compile and run
``` text
 gcc fcfs.c
 ./a.exe
```

 ## sample output
``` text
 enter number of processes: 4
enter arrival time burst time of process: 0 5
enter arrival time burst time of process: 1 3
enter arrival time burst time of process: 2 8
enter arrival time burst time of process: 3 6
```

## sample output
``` text

FCFS SCHEDULING :

PID   AT   BT   CT   TAT   WT
1     0    5    5    5     0
2     1    3    8    7     4
3     2    8    16   14    6
4     3    6    22   19    13

Average Turnaround Time = 11.25
Average Waiting Time = 5.75

Gantt Chart:
| P1 | P2 | P3 | P4 |
0    5    8    16   22
```


```text

in srtf if we want compressed gantt chart ,just uncomment the if condition and print.
```
