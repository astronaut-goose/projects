#include <iostream>
#include <getopt.h> // for getopt_long

#include "task.h"

std::string add;
int pid = 0;

void PrintHelp()
{
    std::cout <<
            "--add    <'task'>:      Add a task to the program\n"
            "--delete <task ID>:     Delete a task\n"
            "--show:                 Lists your tasks\n"
            "--help:                 Show help\n";
    exit(1);
}

void ProcessArgs(int argc, char** argv)
{
    Task task;

    const char* const short_opts = "a:d:sh";
    const option long_opts[] = {
            {"add",       required_argument, nullptr, 'a'},
            {"delete",    required_argument, nullptr, 'd'},
            {"show",      no_argument,       nullptr, 's'},
            {"help",      no_argument,       nullptr, 'h'},
            {nullptr,     0,                 nullptr,   0}
    };

    while (true)
    {
        const auto opt = getopt_long_only(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        case 'a':
            add = std::string(optarg);
            task.addTask(add);
            std::cout << "Task: " << add << " added to the list" << '\n';
            break;

        case 'd':
            pid = std::stof(optarg);
            std::cout << "Deleted: " << pid << std::endl;
            break;

        case 's':
            task.show();
            break;

        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            PrintHelp();
            break;
        }
    }
}

int main(int argc, char** argv)
{
  ProcessArgs(argc, argv);
  Task task2;
  task2.getLastLine();
  return 0;
}
