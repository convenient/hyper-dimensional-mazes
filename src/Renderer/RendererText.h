#ifndef MAZES_FOR_PROGRAMMERS_RENDERERTEXT_H
#define MAZES_FOR_PROGRAMMERS_RENDERERTEXT_H
#include <iostream>
#include <iomanip>

class RendererText {
public:
    static void drawPath(std::vector<Node *> path) {

        if (path.size() <= 2) {
            return;
        }

        Node *start = path.front();
        Node *end = path.back();

        int counter = 0;
        Node *previousNode = nullptr;
        for (auto node : path) {

            std::cout << std::setw(20) << std::left;

            if (node == start) {
                std::cout << "start at";
            } else if (node == end) {
                std::cout << "finish at";
            } else {
                std::cout << previousNode->getPoint().getDifferenceDescription(node->getPoint());
            }

            previousNode = node;
            std::cout  << node->getPoint().getAsString() << std::endl;
        }
    }

    static void drawNodeGoal(Node *start, Node *end) {
        std::cout << start->getPoint().getAsString() << " to " << end->getPoint().getAsString() << std::endl;
    }

};

#endif //MAZES_FOR_PROGRAMMERS_RENDERERTEXT_H
