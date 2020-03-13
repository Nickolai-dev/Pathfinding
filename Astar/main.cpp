#include "main.h"
#include <string.h>
#include <iostream>
#include <boost/algorithm/>
DLL_EXPORT void FindPath(const CsSquaredArray<char> &mesh, CsSquaredArray<char> &result,
                         int x, int y, int ex, int ey, int fixedContainerSize) {
    std::vector<Node*> open, closed;
    std::vector<Node> neighbours;
    Node *start = new Node(y, x, nullptr),
         *end = new Node(ey, ex, nullptr), *current = nullptr;
    open.push_back(start);
    while(open.size() > 0) {
        std::sort(open.begin(), open.end(), [ex, ey](Node* a, Node *b) {
                    int manhattanKoeff = 10;
                    int A = (abs(a->x-ex)+ abs(a->y-ey))*manhattanKoeff+a->nodesTraversedWeight(),
                        B = (abs(b->x-ex)+ abs(b->y-ey))*manhattanKoeff+b->nodesTraversedWeight();
                    return (a > b ? 1 : 0);
                  } // that puts a higher-walued on a top (0-ed) of list
                  );
        current = open[open.size()-1];
        closed.push_back(current);
        open.pop_back();
        neighbours.clear();
        for(int i = -1; i < 2; i++)
            for(int q = -1; q < 2; q++) {
                if (i == 0 && q == 0) continue;
                Node anyNode(current->y+i, current->x+q, nullptr);
                if (anyNode.x < mesh.LowerBound0 || anyNode.x > mesh.Length0) continue;
                if (anyNode.y < mesh.LowerBound1 || anyNode.y > mesh.Length1) continue;
                if (mesh[anyNode.y][anyNode.x] == 0)
                    if(!std::any_of(closed.begin(), closed.end(), [anyNode](Node *node)
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
                if(//shorter path (through current to founded node mbHaveAlrdy)
                   current->nodesTraversedWeight(*mbHaveAlrdy) < (*mbHaveAlrdy)->nodesTraversedWeight()) {
                    (*mbHaveAlrdy)->prev = current;
                } else //useless node, delete/ {
                    delete *mbHaveAlrdy;
                }
            }

            if(node == *end) {
                // write in array
                current = end;
                for(int i = 0; current != nullptr; i++) {
                    if (i > maxContainerSize) throw std::runtime_error("The fixed space is not enough; fix it on C# side; ");
                    result[i][0] = current->y;
                    result[i][1] = current->x;
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
    */
}

std::size_t Node::nodesTraversedWeight() {
    std::size_t i = 0;
    Node *current = this;
    while(current->prev != nullptr) {
        int a = (current->x-current->prev->x), b = (current->y-current->prev->y);
        if(a>1||a<-1||b<-1||b>1) throw std::logic_error("Non nbr node got somewhere in path; ");
        i+=a*b==0?10:14;
    }
    return i;
}

std::size_t Node::nodesTraversedWeight(Node *nbr) {
    int a = (nbr->x-this->x), b = (nbr->y-this->y);
    if(a>1||a<-1||b<-1||b>1) throw std::logic_error("Non nbr node got; ");
    return nodesTraversedWeight()+( a*b==0?10:14 );
}

extern "C" DLL_EXPORT int DllMain(int hinstDLL, int fdwReason, void* lpvReserved) {
    switch (fdwReason) {
    }
    return 1;
}

DLL_EXPORT int sum(int a, int b){return a+b;};
