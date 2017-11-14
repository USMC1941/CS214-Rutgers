// Support for multiple stacks (each one has a mutex)
typedef struct stack {
  int count;
  pthread_mutex_t m; 
  double *values;
} stack_t;

stack_t* stack_create(int capacity) {
  stack_t *result = malloc(sizeof(stack_t));
  result->count = 0;
  result->values = malloc(sizeof(double) * capacity);
  pthread_mutex_init(&result->m, NULL);
  return result;
}
void stack_destroy(stack_t *s) {
  free(s->values);
  pthread_mutex_destroy(&s->m);
  free(s);
}
// Warning no underflow or overflow checks!

void push(stack_t *s, double v) { 
  pthread_mutex_lock(&s->m); 
  s->values[(s->count)++] = v; 
  pthread_mutex_unlock(&s->m); }

double pop(stack_t *s) { 
  pthread_mutex_lock(&s->m); 
  double v = s->values[--(s->count)]; 
  pthread_mutex_unlock(&s->m); 
  return v;
}

int is_empty(stack_t *s) { 
  pthread_mutex_lock(&s->m); 
  int result = s->count == 0; 
  pthread_mutex_unlock(&s->m);
  return result;
}
