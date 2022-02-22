# Philosophers

The Dining Philosophers Problem is a classic example used in computer science to illustrate synchronization problems in the development of parallel algorithms and techniques for solving these problems.

The problem was formulated in 1965 by Edsger Dijkstra as an examination exercise for students. As an example, we took competing access to a tape drive. Soon the problem was formulated by Anthony Hoare in the form in which it is known today.

This project is a training to multi-threads/multi-process programming with the use of mutex and semaphore.
It contains 2 different programs simulating a twist of the famous Dining Philosophers problem, all with the same basic rules.
This project is also a good lesson in C optimization as we need to save every bit of CPU usage we can to ensure the survival of our philosophers.

## Usage 

1. philo: multi-threads and use of mutex

        make && ./philo tm_die_ms tm_eat_ms tm_sleep_ms
 
2. philo_bonus: multi-processes and use of semaphore

        make bonus && ./philo_bonus tm_die_ms tm_eat_ms tm_sleep_ms
