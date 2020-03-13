#ifndef __MAIN_H__
#define __MAIN_H__

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#include <vector>
#include <algorithm>

struct Node {
    int y, x;
    Node *prev;
    Node(int y, int x, Node *prev) : y(y), x(x), prev(prev) {};
    Node() : y(0), x(0), prev(nullptr) {};
    bool operator==(Node another);
    std::size_t nodesTraversedWeight();
    std::size_t nodesTraversedWeight(Node *nbr); /// path weiight including any neighbour last node; throws logicerr
};

template<typename numT>
struct CsSquaredArray {
    int Length() { return reinterpret_cast<int*>(this)[-6]; }
    int GetLength(int axis) { return reinterpret_cast<int*>(this)[-4+axis]; }
    int GetLowerBound(int axis) { return reinterpret_cast<int*>(this)[-2+axis]; }
    numT* operator[] (int index) { return reinterpret_cast<numT*>(this)+GetLength(1)*index; }
};

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT void FindPath(const CsSquaredArray<char> &mesh, CsSquaredArray<char> &result,
                         int x, int y, int ex, int ey, int fixedContainerSize); // DataResult is a container witch fixed on C# side; has fixed size; if owerflow throws exception
DLL_EXPORT int sum(int a, int b);
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
