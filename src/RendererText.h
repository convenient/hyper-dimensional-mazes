#ifndef MAZES_FOR_PROGRAMMERS_RENDERERTEXT_H
#define MAZES_FOR_PROGRAMMERS_RENDERERTEXT_H
#include <iostream>

class RendererText {
public:
    static void drawPath(std::vector<Node *> path) {

        Node *start = path.front();
        Node *end = path.back();

        int counter = 0;
        Node *previousNode = nullptr;
        for (auto node : path) {
            std::cout << ++counter << "/" << path.size() << "\t\t\t\t";
            if (node == start) {
                std::cout << "Start at\t\t";
            } else if (node == end) {
                std::cout << "End at  \t\t";
            } else {
                std::cout << "Move to \t\t";
            }
            std::cout << node->getPoint().getAsString() << std::endl;
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_RENDERERTEXT_H
