using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    class core
    {
        public core( System.Windows.Forms.RichTextBox console )
        {
            SystemIO.initDefaultConsole(console);
        }


        public void Run()
        {
            // matrix functional utilizations
            IMatrix<double> mat = new DMatrix();
            mat.InputFromFileUnsafe("matrix.txt");
            if (mat.Determinant() != 0)
            {
                IVector<double>[] evec = mat.EigenVectors;
                List<double> ev = mat.EigenValues;

                SystemIO.Log("ROOTS!!!::");
                for (int i = 0; i < ev.Count; i++)
                {
                    SystemIO.Log("eigen-number:");
                    SystemIO.Log(ev[i].ToString());

                    SystemIO.Log("eigen-vector:");
                    for (int j = 0; j < evec[i].Value.Length; j++)
                    {
                        SystemIO.Log(evec[i][j].ToString());
                    }
                }
            }
            else
            {
                SystemIO.Log("Ur matri is freaking bad::: k thx");
            }
        }
    }
}
