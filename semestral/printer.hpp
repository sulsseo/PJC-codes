//
// Created by Jakub Trmal on 31/01/2018.
//

using namespace std;

void no_args() {
    cout << "No arguments. Graph to process needed!" << endl;
}

void too_many_args() {
    cout << "Too many arguments given!" << endl;
}

void unknown_arg() {
    cout << "Unknow argument! Please check syntax." << endl;
}

void help() {
    cout <<
            "usage: semestral source_file [options]\n"
                    "\n"
                    "general options:\n"
                    "    -t                     multithread computation\n"
                    "    -h   --help            print help\n"
                    "    -V   --version         print version"
         << endl;
}

void version() {
    cout << "version 1.0" << endl;
}
