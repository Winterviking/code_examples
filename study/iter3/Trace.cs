using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    class Trace<T> : IMatrixNumericCharacteristic<T>
    {
        public T calculate(T[,] mat, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY)
        {
            Number<T> tr = default(T);
            for (int i = 1; i <= registers<T>.Sidelength; i++)
            {
                tr += mat[i, i];
            }

            return tr;
        }
    }
}
