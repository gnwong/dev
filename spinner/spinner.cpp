#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <math.h>
#include <vector>
#include <signal.h>
#include <pthread.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

bool VERBOSE = true;

void usage ();

// Completed functions
void mem_leak_true (time_t delay);
void process (size_t amount, time_t delay);
void mem_eat ();
void mem_leak (time_t delay);
void timer (time_t t);
void sig_handler (int s);
void cpu_collatz (double amount);
void mem_fail (int_fast8_t percent);
void mutex_threads (size_t number, size_t depth);
void *mutex_run (void *arg);

// Globals for the threads
pthread_mutex_t m[100];
int clef = 0;
int mutex_depth = 0;

/*
 * main loop 
 */
int main (int argc, char **argv) {

  /* Set up signal handling */
  signal (SIGINT, sig_handler);
  //signal (SIGTERM, sig_handler);
  signal (SIGQUIT, sig_handler);


  // 0:processes, 1:collatz, 2:mem leak, 3:massive mem, 4: malloc fail
  //    5: threads, 6: true memory leak
  // in units seconds
  int sleep_times [7] = {20, 5, 100, 5, 13, 20, 200};


  /* Way to handle PIDs */
  int pid;
  std::vector<int> PIDs;
  
  /* Set up overall timer */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    timer (3600);
    goto end;
  }
  
  /* Spawn processes */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    process (rand() % 80+10, sleep_times[0]);
  }
  
  for (size_t j=0; j<5; j++) {
    /* Set up CPU resource eater */
    pid = fork();
    PIDs.push_back (pid);
    if (pid == 0) {
      while (true) {
        cpu_collatz ((rand()%70)+25);
        sleep (rand() % sleep_times[1]);
      }
    }
  }
  
  /* Leak memory (controlled) */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    while (true) {
      mem_leak (10); // create a memory leak for 5 seconds
      sleep (rand() % sleep_times[2]);
    }
  }
    
  /* Massive memory usage */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    while (true) {
      mem_eat ();
      sleep (rand() % sleep_times[3]);
    } 
  }

  /* Memory failures */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    while (true) {
      mem_fail (22);
      sleep (rand() % sleep_times[4]);
    }
  }
  
  /* Threads/mutexes failures */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    while (true) {
      mutex_threads (50, 20);
      sleep (rand() % sleep_times[5]);
    }
  }
  
  /* Create a real memory leak */
  pid = fork();
  PIDs.push_back (pid);
  if (pid == 0) {
    while (true) {
    //  mem_leak_true (sleep_times[6]);
      sleep (rand() % sleep_times[6]);
      break;
    }
  }

  /* the end... */
  end:

  /* Wait for timer */
  for (size_t i=0; i<PIDs.size(); i++) {
    waitpid (PIDs.at(i), NULL, 0);
  }
  waitpid (PIDs.at(0), NULL, 0);
  
  /* Worst case... kill everything */
  kill (0, SIGTERM);

  return 0;
}


/* Spawn lots of threads */
/*
 *  Depth has a max value of 100
 */
void mutex_threads (size_t number, size_t depth) {
  
  if (VERBOSE) std::cout << getpid() << ":" << /* std thread << */
          " Spinning up threads" << std::endl;
  
  if (depth > 100) depth = 100;
  pthread_t tid[number];
  
  /* Init mutexes */
  for (size_t i=0; i<depth; i++) {
    mutex_depth = i-1;
    if (pthread_mutex_init (&m[i], NULL) != 0) {
      break;
    }
  }
  mutex_depth = mutex_depth<0 ? 0 : mutex_depth;
  
  for (size_t i=0; i<number; i++) {
    pthread_create(&tid[i], NULL, mutex_run, NULL);
  }
  
  for (size_t i=0; i<number; i++) {
    pthread_join (tid[i], NULL);
  }

  /* Destroy mutexes */
  for (size_t i=0; i<depth; i++) {
    pthread_mutex_destroy (&m[i]);
  }
}

/* 
 * The process that runs for each thread
 */
void * mutex_run (void *arg) {

  for (size_t max = 2; max<mutex_depth+1; max++) {

    for (size_t i=0; i<max; i++) {
      pthread_mutex_lock (&m[i]);
    }
  
    clef++;
  
    for (size_t i=max-1; i>=0; i--) {
      pthread_mutex_unlock (&m[i]);
    }
  
  }

  return NULL;
}

/* 
 * Call malloc a bunch of times and
 * fail according to percentage. Stop
 * calling malloc after delay.
 */
void mem_fail (int_fast8_t percent) {
  if (VERBOSE) std::cout << getpid() << ":" << /* std thread << */
          " Making bad malloc calls" << std::endl;

  for (size_t i=0; i<(2<<20); i++) {
    void *m;
    if (i%(100/percent)) m = malloc (10); // Presumably we have this amount free
    else m = malloc (10000000000000);
    if (!m) break;
    memset (m, 0, i);
    free (m);
  }

}

/* 
 * Write to a bunch of memory and read
 */
void mem_eat () {
  if (VERBOSE) std::cout << getpid() << ":" << /* std thread << */
          " Accessing large amounts of memory" << std::endl;

  unsigned long k=0;
  int size = 2<<29;
  int memSpace[ size ];
  for (size_t i=0; i<size; i++) {
    memSpace[i] = 2;
  }
  
  std::cout << "gomo" << std::endl;
  
  while (k < (2<<22)) {
    k += memSpace[rand()%size];
  }
  
  std::cout << "fini" << std::endl;
}

/*
 * Creates a real memory leak
 *  This is dangerous.
 */
void mem_leak_true (time_t delay) {
  if (VERBOSE) std::cout << getpid() << ":" << /* std thread << */
            " Creating true memory leak" << std::endl;
  
  while (true) {
    void *m = malloc (16*16);
    if (!m) sleep (delay);
    memset (m, 0, 1);
  }
}

/*
 * Create a memory leak
 *  This one is controlled, though,
 *  so it won't crash our system.
 */
void mem_leak (time_t delay) {
  if (VERBOSE)  std::cout << getpid() << ":" << /* std thread << */
          " Leaking memory" << std::endl;

  std::vector<void *> mem_locs;
  while (true) {
    void *m = malloc (2<<8);
    if (!m) continue;
    mem_locs.push_back(m);
    memset (m, 0, 1);
  }
  sleep (delay);
  
  for (size_t i=0; i<mem_locs.size(); i++) {
    free (mem_locs.at(i));
  }
}

/*
 * Spawn new processes
 */
void process (size_t amount, time_t delay) {
  for (size_t i=0; i<amount-4; i++) {
    if (fork() == 0) {
      if (VERBOSE) std::cout << getpid() << ":" << /* thread << */
            " Spawned simple filler process" << std::endl;
       while (true) {
        cpu_collatz (1);
        sleep (rand() % delay);
      }
      break;
    }
  }
}

/*
 * Eat CPU cycles
 */
void cpu_collatz (double amount) {
  if (VERBOSE && amount>1) std::cout << getpid() << ":" << /*std::thread::id << */
          " Computing Collatz" << std::endl;

  unsigned long max = pow ((2<<29), (double)amount/100);


  double x = 0;
  double y = 0;
  
  while (++x < max) {
    y=x;
    while (y!=1) {
      if ((long)y%2) y++;
      else y/=2;
    }
  }
  sleep (1);  // Simulate lull in computation

}

/*
 * Handle signals ( to ensure 
 */
void sig_handler (int s) {
  std::cout << "Termination signal caught, killing all children." << std::endl;
  kill (0, SIGTERM);
}

/*
 *  Simple process that sleeps
 */
void timer (time_t t) {
  sleep (t);
}
