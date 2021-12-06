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
            class MaxLambda<T> : IMatrixNumericCharacteristic<T>
            {
                public double MaxLambda(T[] mat)
                {
                    double Lambda_p = 0, Lambda_n = 50;
                    int side = mat.GetUpperBound(0) + 1;
                    T[] z_next = new T[side];
                    T[] z_prev = new T[side];

                    for (int i = 0; i < side; i++)
                    {
                        z_next[i] = Number<T>.ConvertToNumber(0);
                        z_prev[i] = Number<T>.ConvertToNumber(1); // 1st approximation
                    }

                    // iteration
                    while (Math.Abs(Lambda_n - Lambda_p) > 0.0001)
                    {
                        Lambda_p = Lambda_n;
                        mulMatrixVector(mat, z_prev, z_next);
                        Lambda_n = vecnorm(z_next) / vecnorm(z_prev);
                        copyarray(z_next, z_prev);
                    }

                    return Lambda_n;
                }

            }
        }
    }
}
