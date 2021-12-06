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
            enum E_DETERMINANT_CALCULATION_METHOD
            { 
                GAUSS,
                FLAT
            }
            public class Determinant<T> : IMatrixNumericCharacteristic<T>, IParameters
            {
                public T calculate(T[,] matrix, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY)
                {
                    T res = default(T);
                    if (method == E_DETERMINANT_CALCULATION_METHOD.GAUSS)
                    {
                        if (keep == E_RELATION_OPERATOR_DATA.SAFETY)
                        {
                            T[,] mat = (T[,])matrix.Clone();
                            res = gaussDeterminant(mat);
                        }
                        else if (keep == E_RELATION_OPERATOR_DATA.CORRUPTION)
                        {
                            res = gaussDeterminant(matrix);
                        }
                    }
                    else if (method == E_DETERMINANT_CALCULATION_METHOD.FLAT)
                    { 
                    
                    }
                    return res;
                }

                T gaussDeterminant(T[,] matrix)
                {
                    Number<T> coeff;

                    for (int k = 0; k < registers<T>.Sidelength; k++)
                    {
                        for (int i = k + 1; i < registers<T>.Sidelength; i++)
                        {
                            if (Number<T>.CompareToZero(matrix[k, k]))
                            { break; }
                            else
                            { coeff = Number<T>.negate((Number<T>)matrix[i, k] / matrix[k, k]); }

                            for (int j = k; j < registers<T>.Sidelength; j++)
                            { matrix[i, j] += coeff * matrix[k, j]; }
                        }
                    }

                    Number<T> det = Number<T>.ConvertToNumber(1);
                    for (int i = 0; i < registers<T>.Sidelength; i++)
                    { det *= matrix[i, i]; }

                    return det;
                }

                public void SetParameter(object data, int additionalData = 0)
                {
                    if (data.GetType() == typeof(E_DETERMINANT_CALCULATION_METHOD))
                    {
                        method = (E_DETERMINANT_CALCULATION_METHOD)data;
                    }
                }

                E_DETERMINANT_CALCULATION_METHOD method = E_DETERMINANT_CALCULATION_METHOD.GAUSS;
            }
        }
    }
}
