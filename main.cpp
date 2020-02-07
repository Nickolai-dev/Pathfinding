#include <iostream>
#include "main.h"

using namespace std;

int main() {
    char m[100] = { 0,0,0,0,0,0,0,0,1,1,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,0,0,
                    0,0,0,1,1,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,0,0,
                    0,0,0,1,0,0,0,0,1,1,
                    1,0,0,0,0,0,0,0,0,1,
                    };
    CsSquaredArray mesh = CsArrayFactory::csSquaredArray(m, 10, 10);
    //cout << mesh.Length;
    for(int i = 0; i < mesh.Length1; i++) {
        for(int q = 0; q < mesh.Length0; q++)
            cout << (int)mesh[i][q] << " ";
        cout << endl;
    }
    cout << endl;
    DataResult data = FindPath(mesh, DataConfig(2,4, 6,4));

    return 0;
}
