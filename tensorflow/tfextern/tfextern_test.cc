//
// Created by huang on 11/29/2023.
//

#include "tfextern_test.h"

// Exercises tensorflow's C API.
int main(int argc, char** argv) {
    //TF_InitMain(argv[0], &argc, &argv);

    TF_Graph* graph = tfeNewGraph();
    tfeDeleteGraph(&graph);
}