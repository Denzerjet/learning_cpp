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

        void mark_complete() {
            this->completed = true;
        }


        void do_something_cool() {
            secret();
        }
};

class calendar {
    private:
        std::vector<task> task_list; // new addition
        // everything stored in the vector is stored on the heap since by runtime the stack size must be finalized
        // so nothing dynamic can remain

    public:
        calendar() {}

        void addTask(const task &new_task) { // expects a reference to a task. (a task object)
            // &new_task is pass by reference, so it doesn't make a copy
            // but it still expects just a task object
            task_list.push_back(new_task); // makes a copy of the argument and stores it on the heap
        }

        void deleteTask(int index) {
            if (index < 0 || index >= task_list.size()) {
                std::cout << "Invalid index." << std::endl;
                return;
            }
            // pointer arithmetic
            task_list.erase(task_list.begin() + index);
        }

        void mark_task_complete(int index) {
            task_list[index].mark_complete();
        }

        void printTasks() {
            if (task_list.empty()) {
                std::cout << "No tasks to print." << std::endl;
                std::cout << "Tasks not printed." << std::endl;
                return;
            }

            std::cout << "Printing all tasks:" << std::endl;
            std::cout << "-------------------" << std::endl;
            for (size_t i = 0; i < task_list.size(); i++) {
                std::cout << "Task " + std::to_string(i) + ": "  << std::endl;
                task_list[i].print();
                if (i != task_list.size() -1) {
                    std::cout << "-------------------" << std::endl;
                }
            }
            std::cout << "-------------------" << std::endl;
            std::cout << "All tasks printed." << std::endl;
        }
};

int main() {
    // always match new with delete
    calendar my_calendar; // stack, using new allocs mem on heap

    std::cout << "Welcome to your virtual to-do list!" << std::endl;
    std::cout << std::endl;

    while (true) {
        std::string userInput;

        std::cout << "Please enter a number corresponding to one of the following options." << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Remove Task" << std::endl;
        std::cout << "3. View Tasks" << std::endl;
        std::cout << "4. Mark a task as completed" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << std::endl;

        std::getline(std::cin, userInput);

        if (userInput == "1") {
            // TODO: add input checking later
            std::string task_name;
            int task_month;
            int task_day;
            int task_year;
            std::string newline_eater;

            std::cout << "Please enter the name of the task you'd like to create" << std::endl;
            std::getline(std::cin, task_name);
            std::cout << "Please enter the month of the task" << std::endl;
            std::cin >> task_month;
            std::getline(std::cin, newline_eater); // clean up the newline from reading the ints

            std::cout << "Please enter the day of the task" << std::endl;
            std::cin >> task_day;
            std::getline(std::cin, newline_eater);

            std::cout << "Please enter the year of the task" << std::endl;
            std::cin >> task_year;
            std::getline(std::cin, newline_eater);

            // task *my_task = new task(task_name, task_month, task_day, task_year);
            task my_task(task_name, task_month, task_day, task_year); // stack, whereas above is dynamic alloc
            
            // my_calendar->addTask(*my_task); // arg is the value stored at the pointer, the address of the task object
            my_calendar.addTask(my_task);
        }
        else if (userInput == "2") {
            std::string newline_eater;
            int deletion_index;
            std::cout << "Please enter the index of the task you would like to delete" << std::endl;
            std::cout << "Please note that task indexes start at 0" << std::endl;
            std::cin >> deletion_index;
            std::getline(std::cin, newline_eater);

            my_calendar.deleteTask(deletion_index);
            std::cout << "Task deleted" << std::endl;
        }
        else if (userInput == "3") {
            my_calendar.printTasks();
        }
        else if (userInput == "4") {
            std::string newline_eater;
            int completed_task_index;
            std::cout << "Please enter the index of the task you would like to mark as completed" << std::endl;
            std::cout << "Please note that task indexes start at 0" << std::endl;
            std::cin >> completed_task_index;
            std::getline(std::cin, newline_eater);

            my_calendar.mark_task_complete(completed_task_index);
            std::cout << "Task marked as complete" << std::endl;
        }
        else if (userInput == "5") {
            break;
        }
        else {
            std::cout << "Invalid choice" << std::endl;
            std::cout << "Please enter a number between 1-4, inclusive, and press enter." << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}