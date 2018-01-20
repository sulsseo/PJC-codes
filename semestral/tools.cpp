//
//  tools.cpp
//  semestral
//
//  Created by Jakub Trmal on 03/01/2018.
//  Copyright © 2018 Jakub Trmal. All rights reserved.
//

#include <fstream>
#include <sstream>
#include "tools.hpp"

using namespace std;

void load_graph(std::string path) {
    unsigned int vertices;
    unsigned int edges;

    ifstream file(path);

    file >> vertices;
    file >> edges;
    
}
