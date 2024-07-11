#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Task
{
private:
    int id;
    string description;
    bool isCompleted;

public:
    Task(int id, string description, bool isCompleted=false): id(id), description(description),isCompleted(isCompleted){}

    void markAsCompleted()
    {
        isCompleted = true;
    }
    void markAsIncomplete()
    {
        isCompleted = false;
    }
    string getDescription() const
    {
        return description;
    }
    bool getStatus() const
    {
        return isCompleted;
    }
    int getId() const
    {
        return id;
    }

    static Task fromString(const string& str)
    {
        size_t firstDelim = str.find('|');
        size_t secondDelim = str.find('|', firstDelim + 1);

        int id = stoi(str.substr(0,firstDelim));
        string description = str.substr(firstDelim+1, secondDelim-firstDelim-1);
        bool isCompleted = str.substr(secondDelim+1)=="1";

        return Task(id, description, isCompleted);
    }
    string toString() const
    {
        return to_string(id)+"|"+description+"|"+(isCompleted?"1":"0");
    }
};

class ToDoList
{
private:
    vector<Task> tasks;
    const string filename="tasks.text";

    void loadTaskFromFile()
    {
        ifstream file(filename);

        if(!file.is_open())
        {
            return;
        }

        string line;
        while(getline(file, line))
        {
            tasks.push_back(Task::fromString(line));
        }
        file.close();
    }

    void saveTasksToFile() const
    {
        ofstream file(filename);
        if(!file.is_open())
        {
            cerr<<"\nError opening file for writing"<<endl;
            return;
        }

        for(const auto& task : tasks)
        {
            file<<task.toString()<<endl;
        }
        file.close();

    }
public:
    ToDoList()
    {
        loadTaskFromFile();
    }
    ~ToDoList()
    {
        saveTasksToFile();
    }
    void addTask(const Task& task)
    {
        tasks.push_back(task);
    }
    void removeTask(int id)
    {
        for(auto it = tasks.begin(); it != tasks.end(); ++it)
        {
            if(it->getId() == id)
            {
                tasks.erase(it);
                return;
            }
        }
    }
    Task* findTaskById(int id)
    {
        for(auto& task : tasks)
        {
            if(task.getId() == id)
                return &task;
        }
        return nullptr;
    }

    void markTaskAsCompleted(int id)
    {
        Task* task = findTaskById(id);
        if(task)
        {
            task->markAsCompleted();
        }
    }
    void markTaskAsInComplete(int id)
    {
        Task* task = findTaskById(id);
        if(task)
        {
            task->markAsIncomplete();
        }
    }
    void displayTasks() const
    {
        for(const auto& task:tasks)
        {
            cout<<"Task ID: "<<task.getId()<<", Description: "<<task.getDescription()<<", Status: "<<(task.getStatus() ? "Completed":"Incomplete")<<endl;

        }
    }


};

void displayMenu()
{
    cout<<"\nTo DO List Menu:"<<endl;
    cout<<"\n1. Add Task"<<endl;
    cout<<"\n2. Remove Task"<<endl;
    cout<<"\n3. Mark Task as Completed"<<endl;
    cout<<"\n4. Mark Task as Incomplete"<<endl;
    cout<<"\n5. Display Task"<<endl;
    cout<<"\n6. Exit"<<endl;
    cout<<"\nChoose an option: ";
}

int main()
{
    ToDoList toDoList;
    int choice, id;
    string description;

    while(true)
    {
        displayMenu();
        cin>>choice;

        switch(choice)
        {
        case 1:
            cout<<"Enter Task ID: ";
            cin>>id;
            cin.ignore();
            cout<<"Enter Task Description";
            getline(cin, description);
            toDoList.addTask(Task(id, description));
            break;
        case 2:
            cout<<"Enter Task ID to remove: ";
            cin>>id;
            toDoList.removeTask(id);
            break;
        case 3:
            cout<<"Enter Task ID to Mark as Completed: ";
            cin>>id;
            toDoList.markTaskAsCompleted(id);
            break;
        case 4:
            cout<<"Enter Task ID to Mark as Incomplete: ";
            cin>>id;
            toDoList.markTaskAsInComplete(id);
            break;
        case 5:
            cout<<"Tasks: "<<endl;
            toDoList.displayTasks();
            break;
        case 6:
            cout<<"Exiting ..."<<endl;
            return 0;
        default:
            cout<<"Invalid Choice..."<<endl;
        }
    }
    return 0;
}
