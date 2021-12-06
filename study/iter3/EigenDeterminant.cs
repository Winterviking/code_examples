using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    namespace Math
    {
        namespace ExtServices
        {
            class EigenDeterminant<T> : IFunction<T>, IDataGetterSetter<Matrix<T>>
            {
                public T Function(T argument)
                {
                    T res = default(T);

                    if (matrix_is_ready)
                    {
                        prepare_matrix(argument);
                        res = wmatrix.Determinant(E_RELATION_OPERATOR_DATA.CORRUPTION);
                    }

                    return res;
                }

                void prepare_matrix(T lambda)
                {
                    T[,] arg = matrix.cloneValue();

                    for (int i = 0; i <= arg.GetUpperBound(0); i++)
                    {
                        arg[i, i] -= (Number<T>)lambda;
                    }
                    wmatrix.Value = arg;
                }

                public Matrix<T> data
                {
                    get
                    {
                        return null;
                    }
                    set
                    {
                        if (value.Square)
                        {
                            matrix = value;
                        }
                        else
                        {
                            matrix = null;
                        }
                    }
                }

                Matrix<T> matrix = null;
                Matrix<T> wmatrix = new Matrix<T>();

                bool matrix_is_ready = false;
            }
        }
    }
}
