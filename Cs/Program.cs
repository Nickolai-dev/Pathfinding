using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace Cs {
    struct s { public int x, y; public s(int x, int y) { this.x=x;this.y=y; } };
    class Program {
        [DllImport("Astar.dll", SetLastError = true)]
        static extern void FindPath(int[,] mesh, int[,] result, int x, int y, int ex, int ey);
        [DllImport("Astar.dll", SetLastError = true)]
        static extern int sum(int a, int b);
        unsafe static void Main(string[] args) {
            int[,] mesh = new int[10,10], result = new int[2,1000];
            for (int i = 2; i<8; i++)
                mesh[4, i]=1;
            fixed (void* p1 = mesh, p2= result) {
                //try {
                    FindPath(mesh, result, 0, 0, 8,8);
                //} catch (Exception e) { Console.WriteLine(e+"\n---\n"+ Marshal.GetLastWin32Error()) ; }

            }
            Console.WriteLine(result[0, 0]+" "+result[0, 1]);
        }
    }
}
