#include <iostream>

using namespace std;

int main(){
    
    int passedStudentAmount = 0;
    int allStudents = 0;
    int failedStudents = 0;
    int maxPoints = 0;
    int leastPoints = 99999;
    double scoreAverage = 0;
    bool willContinue = true;
    
    int points = 0;
    int score = 0;
    while (true) {
        if(failedStudents >= 5) break;
        cout << "Input student sccore: ";
        cin >> points;
        if(points <= 100 && points >= 0){
            if(points >= 90){
                score = 10;
            } else if(points >= 80){
                score = 9;
            } else if(points >= 70){
                score = 8;
            } else if(points >= 60){
                score = 7;
            } else if(points >= 50){
                score = 6;
            } else { // neislaike studentai visiskai nesiskaito jokiai statistikai net maziausiu balui
                cout << "Student has failed" << endl;
                failedStudents++;
                cout << "Do you wish to continue? (0|1) ";
                cin >> willContinue;
                if (!willContinue) break;
                continue;
            }
            passedStudentAmount++;
            maxPoints = max(maxPoints, points);
            leastPoints = min(leastPoints, points);
            scoreAverage += score;
        } else {
            cout << "invalid score" << endl;
        }
        cout << "Do you wish to continue? (0|1) ";
        cin >> willContinue;
        if (!willContinue) break;
    }
    allStudents = passedStudentAmount + failedStudents;
    if (passedStudentAmount > 0) {
        scoreAverage /= passedStudentAmount;
    } else {
        scoreAverage = 0;
        leastPoints = 0;
    }
    cout << "Score average: " << scoreAverage << "\nHighest points: " << maxPoints << "\nLowest points: " << leastPoints << "\nFailed student amount: " << failedStudents << "\nStudent passage percentage: " << (float) passedStudentAmount / allStudents * 100 << "%" <<  endl;

    return 0;
}