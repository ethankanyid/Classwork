#ifndef task_h
#define task_h
#include <string>


class Task
{
private:
    int priority;
    string task;
    
public:
    Task();
    ~Task();
    int getPriority();
    void setPriority(int tempPriority);
    string getTask();
    void setTask(string tempTask);
};

Task::Task()
{
    priority = 0;
    task = "";
}

int Task::getPriority()
{
    return priority;
}
void Task::setPriority(int tempPriority)
{
    priority = tempPriority;
}
string Task::getTask()
{
    return task;
}
void Task::setTask(string tempTask)
{
    task = tempTask;
}

#endif /* task_h */
