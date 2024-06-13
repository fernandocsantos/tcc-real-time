typedef void (*task_t)(void *);

void task1(void * data);
void task2(void * data);

void * task1_data, task2_data;

task_t tasks[] = {&task1, &task2, NULL};
void * tasks_data = {task1_data, task2_data};

void setup() {

}

void loop() {

task_manager();
  for(int i = 0; task[i]; i++) task[i](tasks_data[i]);
}



