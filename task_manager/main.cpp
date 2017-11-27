#include <iostream>
#include <getopt.h> // for getopt_long

#include "task.h"

std::string taskName;
int pid = 0;

void PrintHelp()
{
    std::cout <<
            "--add    <'task'>:                 Add a task to the program\n"
            "--delete <task ID>:                Delete a task\n"
            "--update <task ID>:                Choose which task to update\n"
            "--task   <'new task'>:             Name your updated task\n"
            "--show:                            Lists your tasks\n"
            "--help:                            Show help\n";
    exit(1);
}

void ProcessArgs(int argc, char** argv)
{
    Task task;

    const char* const short_opts = "a:d:u:t:sh";
    const option long_opts[] = {
            {"add",       required_argument, nullptr, 'a'},
            {"delete",    required_argument, nullptr, 'd'},
            {"update",    required_argument, nullptr, 'u'},
            {"task",      required_argument, nullptr, 't'},
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
            taskName = std::string(optarg);
            task.addTask(taskName);
            std::cout << "Task: " << taskName << " added to the list" << '\n';
            break;

        case 'd':
            pid = std::stof(optarg);
            task.deleteTask(pid);
            std::cout << "Deleted task number: " << pid << std::endl;
            break;

        case 'u':
            pid = std::stof(optarg);
            break;

        case 't':
            taskName = std::string(optarg);
            task.updateTask(pid, taskName);
            std::cout << "Updated task number: " << pid << std::endl;
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
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    Task checkDB;
    checkDB.checkDB();

    ProcessArgs(argc, argv);
    return 0;
}
