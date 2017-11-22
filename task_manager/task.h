#ifndef TASK_H
#define TASK_H

#include <string>

class Task
{
public:

  //static int pid;         // process id
  //int pid;

  Task();
  ~Task();

  void getLastLine();
  void init();
  void addTask(std::string task_name);
  int generateID();
  //void add();
  void del();
  void show();

};


#endif // TASK_H
