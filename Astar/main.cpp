#include "main.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include <boost/algorithm/cxx11/any_of.hpp>

DLL_EXPORT CsSquaredArray::~CsSquaredArray() {
    delete[] (reinterpret_cast<char*>(this)+28);
}

DLL_EXPORT CsSquaredArray& CsArrayFactory::csSquaredArray(char m[], int width, int height) {
    CsSquaredArray arr;
    arr.Length0 = width;
    arr.Length1 = height;
    arr.Length = width*height;
    arr.LowerBound0 = 0;
    arr.LowerBound1 = 0;
    char *p = new char[arr.Length+28];
    memcpy(p, &arr, 28);
    memcpy(p+28, m, arr.Length);
    return *reinterpret_cast<CsSquaredArray*>(p);
}

DLL_EXPORT const char* CsSquaredArray::operator[](int y) {
    return reinterpret_cast<char*>(this+1)+y*Length0;
}
DLL_EXPORT bool Node::operator==(Node another) {
    return this->x==another.x&&this->y==another.y;
}
DLL_EXPORT void FindPath(CsSquaredArray& mesh, const DataConfig& data, DataResult& result, int maxContainerSize) {
    std::vector<Node*> open, closed;
    std::vector<Node> neighbours;
    Node *start = new Node(data.starty, data.startx, nullptr),
         *end = new Node(data.endy, data.endx, nullptr), *current = nullptr;
    open.push_back(start);
    while(open.size() > 0) {
        std::sort(open.begin(), open.end(), [](Node a, Node b) {return 0;} );
        current = open[open.size()-1];
        closed.push_back(current);
        open.pop_back();
        neighbours.clear();
        for(int i = -1; i < 2; i++)
            for(int q = -1; q < 2; q++) {
                if (i == 0 && q == 0) continue;
                Node anyNode(current.y+i, current.x+q, nullptr);
                if (anyNode.x < mesh.LowerBound0 || anyNode.x > mesh.Length0) continue;
                if (anyNode.y < mesh.LowerBound1 || anyNode.y > mesh.Length1) continue;
                if (mesh[anyNode.y][anyNode.x] == 0)
                    if(!boost::algorithm::any_of(closed.begin(), closed.end(), [anyNode](Node *node)
                                                 { return *node == anyNode; } )) {
                        neighbours.push_back(anyNode);
                    }
            }
        for(Node node : neighbours) {
            node.prev = current;
            auto mbHaveAlrdy = std::find_if(open.begin(), open.end(), [node](Node* eq){ return *eq == node; });
            if(mbHaveAlrdy == open.end()) {
                open.push_back(new Node());
                *open[open.size()-1] = node;
            } else {
                if(/*shorter path (through current to founded node mbHaveAlrdy)*/
                   current->nodesTraversedWeight(*mbHaveAlrdy) < (*mbHaveAlrdy)->nodesTraversedWeight()) {
                    (*mbHaveAlrdy)->prev = current;
                } else /*useless node, delete*/ {
                    delete *mbHaveAlrdy;
                }
            }

            if(node == *end) {
                // write in array
                current = end;
                while(current != nullptr) {
                    // current->y current->x
                    current = current->prev;
                }
                // and delete heap
                for(auto i = closed.begin(); i != closed.end(); i++) {
                    delete *i;
                }
                for(auto i = open.begin(); i != open.end(); i++) {
                    delete *i;
                }
            }
        }
    }
    throw new std::logic_error("Can`t find a path. Probably it doesn`t exist");
}

extern "C" DLL_EXPORT int DllMain(int hinstDLL, int fdwReason, void* lpvReserved) {
    switch (fdwReason) {
    }
    return 1;
}
