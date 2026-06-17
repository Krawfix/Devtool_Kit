#include <iostream>
#include <string>
#include <vector>

class Task
{
private:
    std::string name;
    std::string desc;
    std::string dueDate;
    bool completed;

public:
    Task(const std::string &name, const std::string &desc, const std::string &dueDate) : name(name),
                                                                                         desc(desc),
                                                                                         dueDate(dueDate),
                                                                                         completed(false)
    {
    }

    // For getting Task Name
    std::string getName() const { return name; }

    // For getting Task Description
    std::string getDesc() const { return desc; }

    // For getting Task Data
    std::string getDueDate() const { return dueDate; }

    // For getting completion status
    bool iscCompleted() const { return completed; }

    // Here the value is passed by reference method due to the  use of '&' on the string on the const std::string and '->' variable is used to use the member var inside the object

    // Task name set
    void setName(const std::string &name) { this->name = name; }

    // Task Desc set
    void setDesc(const std::string &desc) { this->desc = desc; }

    // Due Date set
    void setDueDate(const std::string &dueDate) { this->dueDate = dueDate; }

    // Mark the task as completed
    void markCompleted() { completed = true; }

    // Display Task Data
    void displayTask() const
    {

        std::cout << name << " (" << (completed ? "Completed" : "Pending") << ") - Due:" << dueDate << std::endl;
    }
};

class Taskmgr
{
private:
    std::vector<Task> tasks; // List of tasks
public:
    // Displays the Taskmgr Menu for the selection of options via user
    void displayMenu()
    {
        std::cout << "\n -------------------Task-Manager-------------------";
        std::cout << "1. Add Task\n";
        std::cout << "2. Display Tasks\n";
        std::cout << "3. Delete Task\n";
        std::cout << "4. Mark Task as Completed\n";
        std::cout << "5. Edit Task\n";
        std::cout << "6. Exit\n";
    }

    void addTask()
    {
        std::string name, desc, dueDate;
        std::cout << "Enter the Task Name: ";
        // clears a single character from the input buffer
        std::cin.ignore();
        // To capture full name
        getline(std::cin, name);
        std::cout << "Enter Task Description: ";
        getline(std::cin, desc);
        std::cout << "Enter the task Due-Date (YYYY-MM-DD): ";
        getline(std::cin, dueDate);
        //  Using emplace_back: Constructs the Task directly inside the vector
        tasks.emplace_back(name, desc, dueDate);
        std::cout << "Task added successfully!" << std::endl;
    }
    void deleteTask()
    {
        // CHechking whether there are any tasks or NOT
        if (tasks.empty())
        {
            std::cout << "NO Task to delete !" << std::endl;
            return;
        }
        std::cout << "Tasks: " << std::endl;

        for (int i = 0; i < tasks.size(); ++i)
        {
            // FOr getting the Task Names
            std::cout << i + 1 << ". " << tasks[i].getName() << std::endl;
        }
        std::cout << "Enter the Task Number you want to Delete" << std::endl;
        int taskNum;
        std::cin >> taskNum;
        if (taskNum >= 1 && taskNum <= tasks.size())
        {
            tasks.erase(tasks.begin() + taskNum - 1);
            std::cout << "Task Deleted successfully !" << std::endl;
        }
        else
        {
            std::cout << "Invalid Task Number :(" << std::endl;
        }
    }
    // Use Tasks don't use task on function name cuz it will cause confilcts later on
    void displayTasks()
    {
        if (tasks.empty())
        {
            std::cout << "No Tasks to Show !" << std::endl;
            return;
        }
        std::cout << "Tasks: " << std::endl;
        for (int i = 0; i < tasks.size(); ++i)
        {
            // Didn't used endl cuz there will be duplication of number :(
            std::cout << i + 1 << ". ";
            tasks[i].displayTask();
        }
    }

    void markTaskCompleted()
    {
        if (tasks.empty())
        {
            std::cout << "No task to Marks as completed" << std::endl;
            return;
        }
        std::cout << "Tasks: " << std::endl;
        for (int i = 0; i < tasks.size(); ++i)
        {
            std::cout << i + 1 << ". " << tasks[i].getName() << std::endl;
        }
        std::cout << "Enter the Task Number TO Mark as Completed: " << std::endl;
        int taskNum;
        std::cin >> taskNum;
        if (taskNum <= tasks.size() && taskNum >= 1)
        {
            tasks[taskNum - 1].markCompleted();
        }
        else
        {
            std::cout << "INVALID Task Number !" << std::endl;
        }
    }

    void editTask()
    {
        if (tasks.empty())
        {
            std::cout << "No Tasks TO edit" << std::endl;
            return;
        }
        std::cout << "Tasks: " << std::endl;
        for (int i = 0; i < tasks.size(); ++i)
        {
            std::cout << i + 1 << ". " << tasks[i].getName() << std::endl;
        }
        std::cout << "Enter the Task Number to edit" << std::endl;
        int taskNum;
        std::cin >> taskNum;
        if (taskNum <= tasks.size() && taskNum >= 1)
        {
            Task &task = tasks[taskNum - 1];
            std::string name, desc, dueDate;
            std::cout << "Enter NEW task name (current: " << task.getName() << "): ";
            std::cin.ignore();
            std::getline(std::cin, name);
            task.setName(name);

            std::cout << "Enter NEW task Description (current: " << task.getDesc() << "): ";
            std::cin.ignore();
            std::getline(std::cin, desc);
            task.setName(desc);

            task.setName("name");
            task.setDesc("desc");
            task.setDueDate("dueDate");

            std::cout << "Task Updated Successfully" << std::endl;
        }
        else
        {
            std::cout << "Invaliid Task Manager!" << std::endl;
        }
    }

    void run()
    {
        int choice;
        do
        {
            displayMenu();
            std::cout << "Enter your choice\n"
                      << std::endl;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                markTaskCompleted();
                break;
            case 5:
                editTask();
                break;
            case 6:
                std::cout << "Existing Program!!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again!"
                          << std::endl;
            }
        } while (choice != 6);
    }
};

int main()
{
    Taskmgr taskmgr;
    taskmgr.run();
    return 0;
}
