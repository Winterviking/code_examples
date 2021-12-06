using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    namespace Math
    {
        namespace matrix
        {
            class MatrixNorm<T> : IMatrixNumericCharacteristic<T> // TODO :: double or T lel :D
            {
                public T calculate(T[,] mat, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY)
                {
                    T nrm = default(T);
                    for (int i = 0; i <= mat.GetUpperBound(0); i++)
                    {
                        for (int j = 0; j <= mat.GetUpperBound(1); j++)
                        {
                            nrm += (Number<T>)mat[i,j] * mat[i,j];
                        }
                    }

                    return Number<T>.ConvertToNumber(System.Math.Sqrt(Number<T>.getDoubleValue(nrm)));
                }
            }
        }
    }
}
