using System;
using System.Runtime.InteropServices;

namespace Cs {
    class Program {
        [DllImport("Astar.dll")]
        static extern void FindPath(byte[,] mesh, byte[,] result, int x, int y, int ex, int ey, int fixedContainerSize);
        [DllImport("Astar.dll")]
        static extern int sum(int a, int b);
        unsafe static void Main(string[] args) {
            byte[,] mesh = new byte[10,10], result = new byte[2,1000];
            for (int i = 2; i<8; i++)
                mesh[4, i]=1;
            fixed (void* p1 = mesh, p2= result) {
                FindPath(mesh, result, 0, 0, 9, 9, 1000);

            }
            Console.WriteLine(result[0, 0]+" "+result[0, 1]);
        }
    }
}
