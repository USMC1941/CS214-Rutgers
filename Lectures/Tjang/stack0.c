int count;
double values[count];

void push(double v) { values[count++] = v; }
double pop() { return values[--count]; }
int is_empty() { return count == 0; }
