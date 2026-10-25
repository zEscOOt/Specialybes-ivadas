#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string to_lower(string word){
    string str = "";
    for (char c : word)
    {
        c = (int)tolower(c);
        str += c;
    }
    return str;
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

void mark_task_complete(pair<string, bool> tasks[20]){

    int pos;
    while(true){
        cout << "Enter task number: ";
        cin >> pos;
        pos--;
        if(pos < 0 || pos > 20){
            cout << "Invalid task number." << endl;
        } else break;
    }
    
    if(!tasks[pos].second){
        tasks[pos].second = true;
    } else {
        cout << "Task already completed." << endl;
    }
}

void delete_task(pair<string, bool> tasks[20]) // Pos is [1-20]
{
    int pos;
    while(true){
        cout << "Enter task number: ";
        cin >> pos;
        pos--;
        if (pos < 0 || pos > 19)
        {
            cout << "Task out of bounds." << endl;
        } else break;
    }
    
    for(int i = pos; i < 19; i++){
        pair<string, bool> tmp = tasks[i+1];
        tasks[i] = tmp;
        tasks[i+1] = {"", false};
    }
}

void find_word(pair<string, bool> tasks[20])
{
    string word; // doesn't account for leading and trailing spaces
    int matches = 0;
    cout << "Word to search for: ";
    cin >> word;
    word = to_lower(word);
    for(int i = 0; i < 20; i++){
        if(tasks[i].first == "") break;
        int todo_length = tasks[i].first.length();
        for (int j = 0; j < (todo_length - 1); j++){
            string text = tasks[i].first.substr(j, word.length());
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

void sort_task_list(pair<string, bool> tasks[20])
{
    int n = 20;
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            string task1 = to_lower(tasks[j].first);
            string task2 = to_lower(tasks[j].first);
            if (task1.at(0) > task2.at(0))
            {
                swap(tasks[j], tasks[j+1]);
                swapped = true;
            }
        }

        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

void print_task_list_stats(pair<string, bool> tasks[20])
{
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
        if(tasks[i].second) delete_task(tasks);
    }
    
}

int main(){
    pair<string, bool> tasks[20]; // each pair is initilized to "" and false
    // --------------------TESTING PORPUOSES-----------------------------
    // for (int i = 0; i < 20; ++i)
    // {
    //     tasks[i] = {to_string(i + 1), false};
    // }
    //-------------------------------------------------------------------
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
            mark_task_complete(tasks);
            break;

        case '4':
            delete_task(tasks);
            break;

        case '5':
            find_word(tasks);
            break;
        case '6':
            sort_task_list(tasks);
            break;

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