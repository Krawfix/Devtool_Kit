#include <iostream>
#include <string>
#include <vector>

class Task {
    private: 
        std:: string name;
        std:: string desc;
        std:: string dueDate;
        bool completed;
    
    public:
        Task ( const std::string& name, const std::string& desc, const std::string& dueDate):
            name(name),
            desc(desc),
            dueDate(dueDate),
            completed(false)
{
}

// For getting Task Name
std::string getName() const { return name;}

//For getting Task Description
std::string getDesc() const { return desc;}

//For getting Task Data
std::string getDueDate() const { return dueDate;}

// For getting completion status
bool iscCompleted() const { return completed;}


// Here the value is passed by reference method due to the  use of '&' on the string on the const std::string and '->' variable is used to use the member var inside the object 

// Task name set 
void setName(const std::string& name) {this->name = name;}

// Task Desc set
void setDesc(const std::string& desc) {this->desc = desc;}

// Due Date set
void setDueDate( const std::string& dueDate) {this->dueDate = dueDate;}

//Mark the task as completed
void markCompleted() {completed = true;}

//Display Task Data
void displayTask() const {

    std::cout << name << " (" << (completed ? "Completed" : "Pending") << ") - Due:" << dueDate << std::endl;
}
};

class Taskmgr {
    private:
        std::vector <Task> tasks; // List of tasks
    public:
    // Displays the Taskmgr Menu for the selection of options via user
        void displayMenu()
        {
            std::cout << "\n -------------------Task-Manager-------------------";
            std::cout <<"1. Add Task\n";
            std::cout <<"2. Display Tasks\n";
            std::cout <<"3. Delete Task\n";
            std::cout <<"4. Mark Task as Completed\n";
            std::cout <<"5. Edit Task\n";
            std::cout <<"6. Exit\n";
        }
    
    void addTask()
    {
        std::string name, desc, dueDate;
        std::cout << "Enter the Task Name: ";
        //clears a single character from the input buffer
        std::cin.ignore();
        // To capture full name
        getline(std::cin, name);
        std::cout << "Enter Task Description: ";
        getline(std::cin, desc);
        std::cout << "Enter the task Due-Date (YYYY-MM-DD): ";
        getline(std::cin, dueDate);
        //  Using emplace_back: Constructs the Task directly inside the vector
        tasks.emplace_back(name, desc, dueDate);
        std::cout <<"Task added successfully!" << std::endl;
    }
};
