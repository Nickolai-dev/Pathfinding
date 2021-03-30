#include "main.h"
#include <string.h>
#include <iostream>
#include <fstream>


DLL_EXPORT void FindPath(CsSquaredArray<int> &mesh, CsSquaredArray<int> &result,
                         int x, int y, int ex, int ey) {
    std::vector<Node*> open, closed;
    std::vector<Node> neighbours;
    Node *start = new Node(y, x, nullptr),
         *end = new Node(ey, ex, nullptr), *current = nullptr;
    //open.push_back(new Node(5,5,nullptr));
    //open.push_back(new Node(7,7,nullptr));
    open.push_back(start);
    while(open.size() > 0) {
        std::sort(open.begin(), open.end(), [ex, ey](Node* a, Node *b) {
                    int manhattanKoeff = 10;
                    int A = (abs(a->x-ex)+ abs(a->y-ey))*manhattanKoeff+a->nodesTraversedWeight(),
                        B = (abs(b->x-ex)+ abs(b->y-ey))*manhattanKoeff+b->nodesTraversedWeight();
                    std::cout<<"A";
                    return (A > B ? 1 : 0);
                  } // that puts a higher-walued on a bottom (last el) of list
                  ); // need bubble sort
        current = open[open.size()-1];
        closed.push_back(current);
        open.pop_back();
        neighbours.clear();
        for(int i = -1; i < 2; i++)
            for(int q = -1; q < 2; q++) {
                if (i == 0 && q == 0) continue;
                Node anyNode(current->y+i, current->x+q, nullptr);
                if (anyNode.x < mesh.GetLowerBound(1) || anyNode.x > mesh.GetLength(1)) continue;
                if (anyNode.y < mesh.GetLowerBound(0) || anyNode.y > mesh.GetLength(0)) continue;
                if (mesh[anyNode.y][anyNode.x] == 0)
                    if(!std::any_of(closed.begin(), closed.end(), [anyNode](Node *node)
                                                 { return node->x==anyNode.x&&
                                                          node->y==anyNode.y; } )) {
                        neighbours.push_back(anyNode);
                    }
                    std::cout<<"a";
            }
        for(Node node : neighbours) {
            node.prev = current;
            auto mbHaveAlrdy = std::find_if(open.begin(), open.end(), [node](Node* eq){ return eq->x==node.x&&eq->y==node.y; });
            if(mbHaveAlrdy == open.end()) {
                open.push_back(new Node());
                *open[open.size()-1] = node;
            } else {
                if(//shorter path (through current to founded node mbHaveAlrdy)
                   current->nodesTraversedWeight(*mbHaveAlrdy) < (*mbHaveAlrdy)->nodesTraversedWeight()) {
                    (*mbHaveAlrdy)->prev = current;
                } else {//useless node, delete
                    delete *mbHaveAlrdy;
                }
            }

            std::cout << current->x << " " << current->y << std::endl;
            if(node.x==end->x&&node.y==end->y) {
                result[0][0] = open.size();
                result[0][1] = closed.size();
                return;
                // write in array
                current = end;
                for(int i = 0; current != nullptr; i++) {
                    if (i > result.Length()/2) throw std::runtime_error("The fixed space is not enough; fix it on C# side; ");
                    result[0][i] = current->y;
                    result[0][i+1] = current->x;
                    current = current->prev;
                }
                // and delete heap

                for(auto i = closed.begin(); i != closed.end(); i++) {
                    delete *i;
                }
                for(auto i = open.begin(); i != open.end(); i++) {
                    delete *i;
                }
                delete end;
                delete start;
            }
        }
    }
    throw new std::logic_error("Can`t find a path. Probably it doesn`t exist");// */
}

std::size_t Node::nodesTraversedWeight() {
    std::size_t i = 0;
    return 0;
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
