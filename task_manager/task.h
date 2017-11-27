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

    void checkDB();
    void show();
    void addTask(std::string taskName);
    void deleteTask(int taskID);
    void updateTask(int taskID, std::string taskName);


};


#endif // TASK_H
