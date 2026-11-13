#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int manhattan_distance(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }

int main(){
	ifstream file("data.txt");
	string s;
	vector<vector<string>> nums;
	int i = 0;
	float maxDistance = 0;
	pair<int, int> pos;

	while(getline(file, s, ' ')){
		if(s.find('\n') ){
			nums.push_back({});
			i++;
		}
		nums.at(i).push_back(s);
	}

	for(int j = 0; j < nums.size(); j++){
		
	}
	

	return 1;
}
