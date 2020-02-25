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
struct CsSquaredArray;

struct CsArrayFactory  {
    static CsSquaredArray& csSquaredArray(char m[], int width, int height);
};

struct CsSquaredArray {
    friend CsArrayFactory;
    int SyncBlockIndex :32;
    int *MethodTable;
    int Length :32,
        Length0 :32,
        Length1 :32,
        LowerBound0 :32,
        LowerBound1 :32;
    const char* operator[](int y);
    ~CsSquaredArray();
private:
    CsSquaredArray(){};
};

struct DataConfig {
    int startx, starty, endx, endy;
    DataConfig(int x, int y, int ex, int ey) : startx(x), starty(y), endx(ex), endy(ey) {};
};

typedef CsSquaredArray DataResult;

struct Node {
    int y, x;
    Node *prev;
    Node(int y, int x, Node *prev) : y(y), x(x), prev(prev) {};
    Node() : y(0), x(0), prev(nullptr) {};
    bool operator==(Node another);
    size_t nodesTraversedWeight();
    size_t nodesTraversedWeight(Node *nbr); /// path weiight including any neighbour last node; throws logicerr
};

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT void FindPath(CsSquaredArray& mesh, const DataConfig& data, DataResult& result/*fixed*/, int maxContainerSize); // DataResult is a container witch fixed on C# side; has fixed size; if owerflow throws exception

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
