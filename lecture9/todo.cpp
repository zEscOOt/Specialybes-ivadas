#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void to_lower(string &word){
    for (char &c : word)
    {
        c = (int)tolower(c);
    }
}

void add_task(pair<string, bool> tasks[20]){ // This adds the task to the first "empty" position like push_back() on vectors
    string task_name;
    int bounds = 20;

    cout << "Enter task name: ";
    while(true){
        getline(cin, task_name);
        if (task_name == "")
        {
            cout << "Invalid task name." << endl;
            cin.ignore(10000);
            continue;
        } else break;
    }
    
    for(int i = 0; i < bounds; i++){
        if(tasks[i].first == ""){
            tasks[i].first = task_name;
            break;
        } else if(i == bounds - 1){
            cout << "Task list full." << endl;
        }
    }
}

void print_task_list(pair<string, bool> tasks[20]){
    for(int i = 0; i < 20; i++){
        if(tasks[i].first == ""){
            break;
        }
        cout << i+1 << ". " << (tasks[i].second ? "[X] " : "[ ] ") << tasks[i].first << endl;
    }
}

void mark_task_complete(pair<string, bool> tasks[20], int pos){
    if(!tasks[pos].second){
        tasks[pos].second = true;
    } else {
        cout << "Task already completed." << endl;
    }
}

void delete_task(pair<string, bool> tasks[20], int pos)
{
    if(pos < 0 || pos > 20){
        cout << "Task out of bounds.";
        return;
    }
    for(int i = pos; i < 19; i++){
        pair<string, bool> tmp = tasks[i+1];
        tasks[i] = tmp;
    }
}

void find_word(pair<string, bool> tasks[20])
{
    string word; // doesn't account for leading and trailing spaces
    int matches = 0;
    cout << "Word to search for: ";
    cin >> word;
    to_lower(word);
    for(int i = 0; i < 20; i++){
        for (int j = 0; j < tasks[i].first.length() - word.length() - 1; j++){
            string text = tasks[i].first.substr(j, word.length() - 1);
            if(text == word){
                cout << tasks[i].first << endl;
                matches++;
            }
        }
    }

    if(matches == 0){
        cout << "No matches for word: " << word << endl;
    }
}

void print_task_list_stats(pair<string, bool> tasks[20]){
    int num_task = 0;
    int completed_tasks = 0;

    for(int i = 0; i < 20; i++){
        if(tasks[i].first == ""){
            break;
        }
        num_task++;
        if(tasks[i].second) completed_tasks++; 
    }

    cout << "Number of tasks: " << num_task << endl;
    cout << "Completed task number: " << completed_tasks << endl;
    cout << "Tasks left: " << num_task - completed_tasks << endl;
    cout << "Completed task percentage: " << (completed_tasks > 0 ? (100 * (double)completed_tasks/num_task) : 0) << "%" << endl; 
}

void delete_completed_tasks(pair<string, bool> tasks[20])
{
    for (size_t i = 0; i < 20; i++)
    {
        if(tasks[i].second) delete_task(tasks, i);
    }
    
}

int main(){
    pair<string, bool> tasks[20]; // each pair is initilized to "" and false
    int lenght = 0;
    char choice;
    cout << boolalpha;
    while(true){
        cout << "Todo list options:" << endl;
        cout << "1. Add task" << endl;
        cout << "2. Print task list" << endl;
        cout << "3. Mark task complete" << endl;
        cout << "4. Delete task" << endl;
        cout << "5. Find a word in tasks" << endl;
        cout << "6. Sort tasks alphabetically" << endl;
        cout << "7. Print task list statistics" << endl;
        cout << "8. Delete completed tasks" << endl;
        cout << "9. Quit" << endl << endl;
        cout << "Pick an option: ";
        cin >> choice;
        cout << endl;

        switch (choice){
        case '1':
            cin.ignore(10000, '\n');
            add_task(tasks);
            break;

        case '2':
            print_task_list(tasks);
            break;

        case '3':
        {
            int pos;
            cout << "Enter task number: ";
            cin >> pos;
            if (pos >= 0 && pos < 20 && tasks[pos].first != "")
            {
                mark_task_complete(tasks, pos-1);
            }
            else
            {
                cout << "Invalid task number." << endl;
            }
            break;
        }

        case '4':
        {
            int pos;
            cout << "Enter task number: ";
            cin >> pos;
            if (pos >= 0 && pos < 20 && tasks[pos].first != "")
            {
                delete_task(tasks, pos-1);
            }
            else
            {
                cout << "Invalid task number." << endl;
            }
            break;
        }

        case '5':
            // find_word(tasks); broken
            break;

        case '6':
        {
            // TODO: Impletent
            break;
        }

        case '7':
            print_task_list_stats(tasks);
            break;

        case '8':
            delete_completed_tasks(tasks);
            break;
        case 'Q':
        case 'q':
        case '9':
            return 0;

        default:
            cout << "Invalid option." << endl;
            break;
        }
    }



    return 0;
}