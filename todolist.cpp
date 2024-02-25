#include <stdlib.h>
#include <iostream>
#include <memory>
#include "todolist.h"
#include <string>
// using namespace std; i think this is right


class task {
    private:
        bool completed;
        std::string name;
        int due_date[3];

        void secret() {
            std::cout << "This is a secret function" << std::endl;
        }

    public:
        task() {
            completed = false;
            name = "default task name";
            // due_date = {01, 01, 2024}; doesn't work, can only use this initialization syntax at declaration
            due_date[0] = 1;
            due_date[1] = 1;
            due_date[2] = 2024;
        }

        task(std::string name, int month, int day, int year) {
            this->completed = false;
            this->name = name;
            this->due_date[0] = month;
            this->due_date[1] = day;
            this->due_date[2] = year;
        }

        void print() {
            std::cout << "Task name: " + this->name << std::endl;
            if (this->completed) {
                std::cout << "Completion Status: Completed" << std::endl;
            }
            else {
                std::cout << "Completion Status: Incomplete" << std::endl;
            }
            std::cout << "Due date: " + std::to_string(this->due_date[0]) + "/" + std::to_string(this->due_date[1]) 
                                + "/" + std::to_string(this->due_date[2]) << std::endl;
        }


        void do_something_cool() {
            secret();
        }
};

class calendar {
    private:
        int num_tasks;
        int list_size;
        task task_list[10];

    public:
        calendar() : num_tasks(0), list_size(10) { // initializer list syntax, inits num_tasks to 0 and list_size to 10

        }

        void addTask(task new_task) {
            if (num_tasks == list_size) {
                std::cout << "List full. Please delete a task before adding more." << std::endl;
                std::cout << "Task not added." << std::endl;
                return;
            }
            task_list[num_tasks] = new_task;
            num_tasks++;
        }

        void deleteTask(int index) {
            if (index >= list_size || index < 0) {
                std::cout << "Invalid index. Bounds are 0 <= index <= " + std::to_string(list_size - 1) << std::endl;
                std::cout << "Task not deleted." << std::endl;
                return;
            }
            // delete task_list[index]; it wasn't dynamically allocated so no need to call delete
            for (int i = index; i < num_tasks - 1; i++) {
                task_list[i] = task_list[i + 1];
            }
            
            num_tasks--;
        }

        void printTasks() {
            if (num_tasks == 0) {
                std::cout << "No tasks to print." << std::endl;
                std::cout << "Tasks not printed." << std::endl;
                return;
            }

            std::cout << "Printing all tasks:" << std::endl;
            std::cout << "-------------------" << std::endl;
            for (int i = 0; i < num_tasks; i++) {
                std::cout << "Task " + std::to_string(i) + ": "  << std::endl;
                task_list[i].print();
                if (i != num_tasks -1) {
                    std::cout << "-------------------" << std::endl;
                }
            }
            std::cout << "-------------------" << std::endl;
            std::cout << "All tasks printed." << std::endl;
        }
};

int main() {
    // std::cout << "Hello world" << std::endl;

    // task *first_task = new task("ml exam prep", 2, 25, 2024);

    // first_task->do_something_cool();

    // first_task->print();


    // std::string userInput;
    
    // std::cout << "Please enter a line of text:" << std::endl;
    
    // // Get the entire line from standard input and store it in userInput
    // std::getline(std::cin, userInput);
    
    // std::cout << "You entered: " << userInput << std::endl;

    calendar *my_calendar = new calendar();
    task *first_task = new task("ml exam prep", 2, 25, 2024);
    my_calendar->addTask(*first_task);

    my_calendar->printTasks();

    my_calendar->deleteTask(0);

    my_calendar->printTasks();


    return 0;
}