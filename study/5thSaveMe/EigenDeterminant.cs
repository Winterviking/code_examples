using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    namespace Math
    {
        namespace ExtServices
        {
            class EigenDeterminant<T> : IFunction<T>
            {
                public EigenDeterminant( IMatrix<T> mat )
                {
                    matrix = mat;
                    matrix_is_ready = true;
                    if (typeof(DMatrix) == mat.GetType())
                    {
                        wmatrix = (IMatrix<T>)(object)new DMatrix();
                    }
                }

                public T Function(T argument)
                {
                    T res = default(T);

                    if (matrix_is_ready)
                    {
                        prepare_matrix(argument);
                        res = wmatrix.Determinant(E_DETERMINANT_CALCULATION_METHOD.GAUSS, E_RELATION_OPERATOR_DATA.CORRUPTION);
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

                public IMatrix<T> data
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

                IMatrix<T> matrix = null;
                IMatrix<T> wmatrix;

                bool matrix_is_ready = false;
            }
        }
    }
}
