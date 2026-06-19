#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

const std::string TASKS_FILE = "tasks.txt";

class Task
{
private:
    std::string name;
    std::string desc;
    std::string dueDate;
    bool completed;

public:
    Task(const std::string &name, const std::string &desc, const std::string &dueDate, bool completed = false) : name(name),
                                                                                                                    desc(desc),
                                                                                                                    dueDate(dueDate),
                                                                                                                    completed(completed)
    {
    }

    // For getting Task Name
    std::string getName() const { return name; }

    // For getting Task Description
    std::string getDesc() const { return desc; }

    // For getting Task Data
    std::string getDueDate() const { return dueDate; }

    // For getting completion status
    bool isCompleted() const { return completed; }

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
        std::cout << name << " (" << (completed ? "Completed" : "Pending") << ") - Due: " << dueDate;
        if (!desc.empty())
            std::cout << "\n     " << desc;
        std::cout << std::endl;
    }

    // Serializes the task into one line so it can be written to the save file.
    // Fields are separated by '|' and the desc/dueDate are not allowed to contain it (sanitized on input).
    std::string serialize() const
    {
        return name + "|" + desc + "|" + dueDate + "|" + (completed ? "1" : "0");
    }
};

class Taskmgr
{
private:
    std::vector<Task> tasks; // List of tasks

    // Reads one full line of input safely; loops until something non-empty is given if required=true
    static std::string readLine(const std::string &prompt, bool required = true)
    {
        std::string line;
        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, line);
            // strip a stray '|' so it can't break the save-file format
            for (char &c : line)
                if (c == '|')
                    c = '/';
            if (!required || !line.empty())
                return line;
            std::cout << "This field can't be empty, please try again.\n";
        }
    }

    // Reads an integer safely, re-prompting on bad input instead of looping forever
    static int readInt(const std::string &prompt)
    {
        int value;
        while (true)
        {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a valid number.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }

    // Prints the task list with index numbers; returns false if there's nothing to show
    bool listTasks(const std::string &emptyMsg)
    {
        if (tasks.empty())
        {
            std::cout << emptyMsg << std::endl;
            return false;
        }
        std::cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i)
            std::cout << i + 1 << ". " << tasks[i].getName() << std::endl;
        return true;
    }

    // Asks for a task number and validates it's within range; returns -1 on invalid input
    int pickTaskIndex(const std::string &prompt)
    {
        int taskNum = readInt(prompt);
        if (taskNum < 1 || static_cast<size_t>(taskNum) > tasks.size())
        {
            std::cout << "Invalid task number!" << std::endl;
            return -1;
        }
        return taskNum - 1;
    }

public:
    // Displays the Taskmgr Menu for the selection of options via user
    void displayMenu()
    {
        std::cout << "\n -------------------Task-Manager------------------- \n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Display Tasks\n";
        std::cout << "3. Delete Task\n";
        std::cout << "4. Mark Task as Completed\n";
        std::cout << "5. Edit Task\n";
        std::cout << "6. Save & Exit\n";
        std::cout << "----------------------------------------------------\n";
    }

    void addTask()
    {
        // readLine handles the leftover-newline issue and rejects empty names
        std::string name = readLine("Enter the Task Name: ");
        std::string desc = readLine("Enter Task Description (optional): ", false);
        std::string dueDate = readLine("Enter the task Due-Date (YYYY-MM-DD): ");
        //  Using emplace_back: Constructs the Task directly inside the vector
        tasks.emplace_back(name, desc, dueDate);
        std::cout << "Task added successfully!" << std::endl;
    }

    void deleteTask()
    {
        // CHechking whether there are any tasks or NOT
        if (!listTasks("NO Task to delete !"))
            return;
        int idx = pickTaskIndex("Enter the Task Number you want to Delete: ");
        if (idx == -1)
            return;
        std::string removedName = tasks[idx].getName();
        tasks.erase(tasks.begin() + idx);
        std::cout << "Task \"" << removedName << "\" Deleted successfully !" << std::endl;
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
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            // Didn't used endl cuz there will be duplication of number :(
            std::cout << i + 1 << ". ";
            tasks[i].displayTask();
        }
    }

    void markTaskCompleted()
    {
        if (!listTasks("No task to Mark as completed"))
            return;
        int idx = pickTaskIndex("Enter the Task Number TO Mark as Completed: ");
        if (idx == -1)
            return;
        if (tasks[idx].isCompleted())
            std::cout << "That task is already marked completed." << std::endl;
        else
        {
            tasks[idx].markCompleted();
            std::cout << "Task marked as completed!" << std::endl;
        }
    }

    void editTask()
    {
        if (!listTasks("No Tasks TO edit"))
            return;
        int idx = pickTaskIndex("Enter the Task Number to edit: ");
        if (idx == -1)
            return;

        Task &task = tasks[idx];
        std::cout << "Leave a field blank to keep its current value.\n";

        std::string name = readLine("Enter NEW task name (current: " + task.getName() + "): ", false);
        if (!name.empty())
            task.setName(name);

        std::string desc = readLine("Enter NEW task Description (current: " + task.getDesc() + "): ", false);
        if (!desc.empty())
            task.setDesc(desc);

        std::string dueDate = readLine("Enter New Due Date (current: " + task.getDueDate() + "): ", false);
        if (!dueDate.empty())
            task.setDueDate(dueDate);

        std::cout << "Task Updated Successfully" << std::endl;
    }

    // Loads previously saved tasks from TASKS_FILE, if it exists
    void loadTasks()
    {
        std::ifstream in(TASKS_FILE);
        if (!in.is_open())
            return; // first run, nothing to load

        std::string line;
        while (std::getline(in, line))
        {
            if (line.empty())
                continue;
            std::stringstream ss(line);
            std::string name, desc, dueDate, completedFlag;
            std::getline(ss, name, '|');
            std::getline(ss, desc, '|');
            std::getline(ss, dueDate, '|');
            std::getline(ss, completedFlag, '|');
            tasks.emplace_back(name, desc, dueDate, completedFlag == "1");
        }
    }

    // Writes all tasks to TASKS_FILE so they persist between runs
    void saveTasks()
    {
        std::ofstream out(TASKS_FILE);
        if (!out.is_open())
        {
            std::cout << "Warning: could not save tasks to disk." << std::endl;
            return;
        }
        for (const auto &t : tasks)
            out << t.serialize() << "\n";
    }

    void run()
    {
        loadTasks();
        int choice;
        do
        {
            displayMenu();
            choice = readInt("Enter your choice: ");

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
                saveTasks();
                std::cout << "Tasks saved. Exiting Program!!" << std::endl;
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