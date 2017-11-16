#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

class Todo{
    public:
        Todo() {}

        Todo(string x){
            this->x = x;
        }

        void set_x(string x){
            this->x = x;
        }
        string get_x(){
            return x;
        }

        void set_prio(int prio){
            this->prio = prio;
        }
        int get_prio(){
            return prio;
        }

        void set_done(string done){
            this->done = done;
        }
        string get_done(){
            return done;
        }

    private:
        string x;
        string done;
        int prio;

};

class Storage{
    public:
        void menu();
        void command();
        void new_task();
        int write_to_file();
        int read_from_file();
        void list_tasks();
        void remove_task();
        void completes_task();
        void priority_to_task();
        void list_tasks_priority();

    private:
         vector<Todo> storage;
         Todo t;

};


void Storage::new_task()
{
    string user_input;
    getline(cin, user_input);

    t = Todo(user_input);
    storage.push_back(t);

}

int Storage::write_to_file()
{
    ofstream outfile;
    outfile.open("probe.txt");

    outfile << "No. | Task name | Task priority | Done? |" <<endl;
    for(int i = 0; i < storage.size(); i++){
        outfile << i+1 << "\t" <<storage.at(i).get_x() << "\t" << storage.at(i).get_done() << "\t" << storage.at(i).get_prio() << "\t" << endl;
    }

    outfile.close();
}

int Storage::read_from_file()
{
    ifstream infile;
    infile.open("probe.txt");

    cout << "List tasks by number" <<endl;
    cout << "No. | Task name | Task priority | Done? |" <<endl;
    for(int i = 0; i < storage.size(); i++){
        cout << i+1 << "\t" <<storage.at(i).get_x() << "\t" << storage.at(i).get_done() << "\t" << storage.at(i).get_prio() << "\t" <<endl;
    }

    infile.close();
}

void Storage::list_tasks()
{
    cout << "List tasks by number" <<endl;
    cout << "No. | Task name | Task priority | Done? |" <<endl;
    for(int i = 0; i < storage.size(); i++){
        cout << i+1 << "\t" <<storage.at(i).get_x() << "\t" << storage.at(i).get_done() << "\t" << storage.at(i).get_prio() << "\t" <<endl;
    }

}

void Storage::remove_task()
{
    int size1 = 0;
    int user_input;

    cout << "Remove task int given number: ";
    cin >> user_input;
    cout << endl;

    size1 = storage.size();
    storage.erase(storage.begin()+user_input-1);
    storage.resize(size1-1);
}

void Storage::completes_task()
{
    int user_input;

    cout << "Remove task int given number: ";
    cin >> user_input;
    cout << endl;

    for(int i = 0; i < storage.size(); i++){
        cout << i+1 << "\t" <<storage.at(i).get_x() << "\t" << "[x]" << "\t" << storage.at(i).get_prio() << "\t" <<endl;
    }

    /*
    int i = 0;
    int input_number = strtol(user_input, NULL, 10);
    printf("No. | Done? | Task priority | Task name \n");
    for(i = 0; i < counter; i++){
        if(i == input_number-1){
             //printf("%d. [x]   Priority: 1 %s", i+1, todo_arr[i].task_name);
        } else {
             //printf("%d. [ ]   Priority: 1 %s", i+1, todo_arr[i].task_name);
        }

    }
    */
}

void Storage::priority_to_task()
{
    /*
    int i = 0;
    int input_number = strtol(user_input, NULL, 10);
    for(i = 0; i < counter; i++){
        if(i == input_number-1){
             printf("%d. [x] prio:  %d %s", i+1, input_number, todo_arr[i].task_name);
        } else {
             printf("%d. [ ] prio:  %s", i+1, todo_arr[i].task_name);
        }
    }
    */

      /*
            cout << "Write two numbers: a task number and give priority to it!" << endl;
            i = 0;
            for(i = 0; i < counter; i++){
                scanf"(%d", tasknum);
                scanf("%d", prio);
                printf("%d. [x] prio:  %d %s", i+1, input_number, todo_arr[i].task_name);
            }

            priority_to_task(todo_arr, user_input);
            */
}

void Storage::list_tasks_priority(){
    /*
    int i = 0;
    int input_number = strtol(user_input, NULL, 10);
    for(i = 0; i < counter; i++){
        if(i == input_number-1){
             printf("%d. [x] %s", i+1, todo_arr[i].task_name);
        } else {
             printf("%d. [ ] %s", i+1, todo_arr[i].task_name);
        }
    }
    */

}


void Storage::command(){
  string command;

    do {
        cin >> command;
        if (command == "exit") {
            cout << "The program is exiting now. Goodbye!" << endl;
            exit(0);
        } else if (command == "clr") {
            system("cls");
            continue;
        } else if (command == "menu") {
            menu();
            continue;
        } else if(command == "-a"){
            new_task();

        } else if (command == "-wr") {
            write_to_file();

        } else if (command == "-rd") {
           read_from_file();

        } else if (command == "-l") {
            list_tasks();

        } else if (command == "-e") {
            write_to_file();

        } else if (command == "-rm") {
            remove_task();

        } else if (command == "-c") {
           completes_task();

        } else if (command == "-p") {
            priority_to_task();

        } else if (command == "-lp") {
            list_tasks_priority();

        } else {
            cout << "Wrong task name. Look at the possible tasks again." << endl;
        }

    } while (command != "exit");

}

void Storage::menu() {
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "|        Todo application                |" << endl;
    cout << "------------------------------------------" << endl;
    cout << "| Commands:                              |" << endl;
    cout << "| -a    Adds a new task                  |" << endl;
    cout << "| -wr   Write current todos to file      |" << endl;
    cout << "| -rd   Read todos from a file           |" << endl;
    cout << "| -l    Lists all the tasks              |" << endl;
    cout << "| -e    Empty the list                   |" << endl;
    cout << "| -rm   Removes a task                   |" << endl;
    cout << "| -c    Completes a task                 |" << endl;
    cout << "| -p    Add priority to a task           |" << endl;
    cout << "| -lp   Lists all the tasks by priority  |" << endl;
    cout << "------------------------------------------" << endl;
    cout << "| menu  Opens the main menu              |" << endl;
    cout << "| clr   Clear command line               |" << endl;
    cout << "| exit  Exiting from the program         |" << endl;
    cout << "------------------------------------------" << endl;
    system("pause");
    system("cls");
}
int main()
{
    Storage s;
    s.menu();
    s.command();
    return 0;
}
