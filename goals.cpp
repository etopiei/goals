#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

std::vector<int> goalNumbers;
std::vector<std::string> goalNames;

void readInGoals() {
	std::ifstream myFile;
	std::string home = getenv("HOME");
	myFile.open((home + "/scripts/goals.txt").c_str());

	int count = 0;

	std::string line;
	while(std::getline(myFile, line)) {
		if(count%3==0) {
			goalNames.push_back(line);
		} else {
			std::istringstream iss(line);
			int num;
			iss >> num;
			goalNumbers.push_back(num);
		}
		count += 1;
	}
}

void writeOutGoals() {
	std::ofstream myFile;
	std::string home = getenv("HOME");
	myFile.open((home + "/scripts/goals.txt").c_str());

	for(int i = 0; i < goalNames.size(); i++) {
		myFile << goalNames[i] << std::endl;
		myFile << goalNumbers[2*i] << std::endl;
		myFile << goalNumbers[2*i+1] << std::endl;
	}
	myFile.close();
}

std::string showUsage() {
	std::string usage = "Usage:\n";
	usage += "goals [option]\n";
	usage += "\nOptions:\n";
	usage += "show - Shows all goals and their progress\n";
	usage += "add - Add toward goal\n";
	usage += "sub - Subtract from goal\n";
	usage += "new - Create a new goal\n";
	usage += "delete - Delete a goal\n";
	usage += "help - Show this screen\n";
	return usage;
}

std::string selectGoal() {
	std::string output = "\n";
	for(int i = 0; i < goalNames.size(); i++) {
		output += std::to_string(i+1);	
		output += ". ";
		output += goalNames[i];
		output += "\n";
	}
	output += "\n";
	return output;
}

std::string printGoals() {
	std::string output = "\n";
	for(int i = 0; i < goalNames.size(); i++) {
		output += goalNames[i] + ": ";
		int max = goalNumbers[2*i];
		int current = goalNumbers[2*i+1];
		float percent = (float)current/max*100;
		output += "<";
		for(float j = 0; j < percent/3; j++) {
			output += "#";
		}
		for(float j = 0; j < 33-(percent/3); j++) {
			output += " ";
		}	
		output += "> ";
	    output += std::to_string(std::trunc(100*percent)/100);
		output += "%";
		output += " (";
		output += std::to_string(current);
		output += "/";
		output += std::to_string(max);
		output += ")";
		output += "\n";
	}
	output += "\n";
	return output;
}

void addToGoal(bool adding) {
		int choice = 0;
		int change = 0;
		std::cout << selectGoal();
		if(adding) {
			std::cout << "Select a goal from above to add to: ";
		} else {
			std::cout << "Select a goal from above to subtract from: ";
		}
		std::cin >> choice;
		if(adding) {
			std::cout << "How much would you to add to this goal: ";
		} else {
			std::cout << "How much would you like to subtract from this goal: ";
		}
		std::cin >> change;
		goalNumbers[2*(choice-1)+1] += change; //TODO: Check if this completes goal	or goes below 0
}

void deleteGoal() {
	int choice = 0;
	std::cout << selectGoal();
	std::cout << "Select a goal to delete: ";
	std::cin >> choice;
	goalNames.erase(goalNames.begin() + choice - 1);
}

void newGoal() {
	std::string goalName;
	std::cout << "Enter the name of your new goal: ";
	std::getline(std::cin, goalName);
	goalNames.push_back(goalName);
	int max = 0;
	int current = 0;
	std::cout << "What integer are you aiming for: ";
	std::cin >> max;
	std::cout << "What are you up to now: ";
	std::cin >> current;
	goalNumbers.push_back(max);
	goalNumbers.push_back(current);
}

int main(int argc, char **argv) {

		if(argc < 2) {
				std::cout << showUsage();
				return 0;
		} 
		std::string option(argv[1]);
		readInGoals();

		if(option == "show") {
				std::cout << printGoals();
		} else if(option == "add") {
				addToGoal(true);
		} else if(option == "sub") {
				addToGoal(false);
		} else if(option == "delete") {
				deleteGoal();
		} else if(option == "new") {
				newGoal();
		} else {
				std::cout << showUsage();
		}
		writeOutGoals();
		return 0;
}
