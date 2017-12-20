#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include "ProgressBar.h"
#include "Goal.h"

#define PROGRESS_BAR_SIZE 33

void readInGoals(std::vector<Goal>& goals_) {
	std::ifstream myFile;
	std::string home = getenv("HOME");
	myFile.open((home + "/scripts/goals.txt").c_str());

	int count = 0;

	std::string line;
	while(std::getline(myFile, line)) {
            std::string goalName = line;

            //read max
            std::getline(myFile, line);
            unsigned goalMax = std::stoul(line);

            //read current
            std::getline(myFile, line);
            unsigned goalCurrent = std::stoul(line);
            goals_.push_back(Goal(goalName, goalMax, goalCurrent));
        }
        myFile.close();
}

void writeOutGoals(const std::vector<Goal>& goals_) {
    std::ofstream myFile;
    std::string home = getenv("HOME");
    myFile.open((home + "/scripts/goals.txt").c_str());
    
    for(const Goal& goal: goals_){
        //std::cout << goal.toString();
        myFile << goal.toString();
    }
    myFile.close();
}

std::string showUsage() {
    std::ostringstream oss;
    oss << "Usage:\n"
        << "goals [option]\n"
        << "\nOptions:\n"
        << "show - Shows all goals and their progress\n"
        << "add - Add toward goal\n"
        << "sub - Subtract from goal\n"
        << "new - Create a new goal\n"
        << "delete - Delete a goal\n"
        << "help - Show this screen\n";

    return oss.str();
}

/* 
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
 */

std::string getGoalListString(const std::vector<Goal>& goals_) {
    std::ostringstream oss;
    for(unsigned i = 0; i < goals_.size(); i++){
        oss << i+1 << ". " << goals_[i].getName() << ": "
            << ProgressBar(goals_[i].getCurrent(),goals_[i].getMax(),PROGRESS_BAR_SIZE).toString()
            << std::endl;
    }
    return oss.str();
}

bool editGoal(bool adding, std::vector<Goal>& goals_) {
		int choice = 0;
		int change = 0;
		std::cout << getGoalListString(goals_);
		if(adding) {
			std::cout << "Select a goal from above to add to: ";
		} else {
			std::cout << "Select a goal from above to subtract from: ";
		}
		std::cin >> choice;

                if(choice < 1 || choice > goals_.size()){
                    std::cout << "Invalid choice";
                    return false;
                }
                
		if(adding) {
			std::cout << "How much would you to add to this goal: ";
		} else {
			std::cout << "How much would you like to subtract from this goal: ";
		}
		std::cin >> change;

                goals_[choice-1].incrementBy(change*(adding?1:-1));
//		goalNumbers[2*(choice-1)+1] += change; //TODO: Check if this completes goal	or goes below 0
                return true;
}

bool deleteGoal(std::vector<Goal>& goals_) {
	int choice = 0;
	std::cout << getGoalListString(goals_) << std::endl;
	std::cout << "Select a goal to delete: ";
	std::cin >> choice;

        if(choice < 1 || choice > goals_.size()){
            std::cout << "Invalid choice";
            return false;
        }
        
        goals_.erase(goals_.begin() + choice - 1);
        return true;
}

bool newGoal(std::vector<Goal>& goals_) {
	std::string goalName;
	std::cout << "Enter the name of your new goal: ";
	std::getline(std::cin, goalName);
	int max = 0;
	int current = 0;
	std::cout << "What integer are you aiming for: ";
	std::cin >> max;
	std::cout << "What are you up to now: ";
	std::cin >> current;

        if(current > max){
            std::cout << "Invalid input";
            return false;
        }
        
        goals_.push_back(Goal(goalName, max, current));

        return true;
}

int main(int argc, char **argv) {
    std::vector<Goal> goals;
    bool isGoalListChanged = false;
    
		if(argc < 2) {
				std::cout << showUsage();
				return 0;
		} 
		std::string option(argv[1]);
		readInGoals(goals);

		if(option == "show") {
                    std::cout << getGoalListString(goals);
		} else if(option == "add") {
                    isGoalListChanged = editGoal(true, goals);
		} else if(option == "sub") {
                    isGoalListChanged = editGoal(false, goals);
		} else if(option == "delete") {
                    isGoalListChanged = deleteGoal(goals);
		} else if(option == "new") {
                    isGoalListChanged = newGoal(goals);
		} else {
                    std::cout << showUsage();
		}
                
		if(isGoalListChanged) {
                    writeOutGoals(goals);
                }
		return 0;
}
