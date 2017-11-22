#include "task.h"
#include <iostream>
#include <fstream>
#include <string>

Task::Task(){};
Task::~Task(){};


void Task::show()
{
  std::ifstream inf("tekst.txt");

  std::cout << "Your available tasks: " << '\n';

  while(inf){
    std::string strInput;
    getline(inf, strInput);
    std::cout << strInput << '\n';
  }
}
void Task::getLastLine()
{
  /*
  std::ifstream inf;
  std::string filename = "tekst.txt";
  inf.open(filename);

  inf.seekg(-1, std::ios_base::end);

  std::string lastLine;
  getline(inf, lastLine);
  std::cout << lastLine << '\n';
  */

  std::string filename = "tekst.txt";
    std::ifstream fin;
    fin.open(filename);
    if(fin.is_open()) {
        fin.seekg(0, std::ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while(keepLooping) {
            char ch = ' ';
            fin.seekg(-2, std::ios_base::cur);                            // Get current byte's data

            if((int)fin.tellg() <= 0) {             // If the data was at or before the 0th byte
                fin.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if(ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                fin.seekg(-2, std::ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }

        std::string lastLine;
        getline(fin,lastLine);                      // Read the current line
        std::cout << "Result: " << lastLine << '\n';     // Display it

        fin.close();
    }
}

int Task::generateID()
{
  static int pid = 0;
  return pid++;
}
void Task::addTask(std::string task_name)
{
  static int pid = 1;
  std::ofstream outf("tekst.txt", std::ios::app);

  outf << generateID() << " " << task_name << '\n';
  //outf << task_name << '\n';
}
