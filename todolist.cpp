#include <stdlib.h>
#include <iostream>
#include <memory>
#include "todolist.h"
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

int main() {
    // std::cout << "Hello world" << std::endl;

    task *first_task = new task("ml exam prep", 2, 25, 2024);

    // first_task->do_something_cool();

    first_task->print();
    


    return 0;
}