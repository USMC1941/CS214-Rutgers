int count;
double values[count];
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void push() { pthread_mutex_lock(&m1); values[count++] = values; pthread_mutex_unlock(&m1); }
double pop() { pthread_mutex_lock(&m2); double v=values[--count]; pthread_mutex_unlock(&m2); return v;}
int is_empty() { pthread_mutex_lock(&m1); return count == 0; pthread_mutex_unlock(&m1); }
