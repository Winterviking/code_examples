using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    namespace Math
    {
        public enum E_DETERMINANT_CALCULATION_METHOD
        {
            GAUSS,
            FLAT
        }

        public class ArrayOps<T>
        {
            public T Determinant(T[,] matrix, E_DETERMINANT_CALCULATION_METHOD method = E_DETERMINANT_CALCULATION_METHOD.GAUSS, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY)
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
                    // TODO::yes
                }
                return res;
            }

            public T gaussDeterminant(T[,] matrix)// Gauss determinant
            {
                Number<T> coeff = default(T);

                int side = matrix.GetUpperBound(0) + 1;

                for (int k = 0; k < side; k++)
                {
                    
                    for (int i = k + 1; i < side; i++)
                    {
                        bool good = false;
                        if (Number<T>.CompareToZero(matrix[k, k]))
                        {
                            for (int j = i; j < side; j++)
                            {
                                if (!Number<T>.CompareToZero(matrix[j, k]))
                                {
                                    for (int l = k; l < side; l++)
                                    {
                                        matrix[k, l] += (Number<T>)matrix[j, l];
                                    }
                                    good = true;
                                    break;
                                }
                            }
                        }
                        else
                        { good = true; }
                        
                        if (!good)
                        {
                            matrix[k, k] = Number<T>.ConvertToNumber(0.000000000000001);
                        }

                        coeff = Number<T>.negate((Number<T>)matrix[i, k] / matrix[k, k]);

                        for (int j = k; j < side; j++)
                        { matrix[i, j] += coeff * matrix[k, j]; }
                    }
                }

                Number<T> det = Number<T>.ConvertToNumber(1);
                for (int i = 0; i <= matrix.GetUpperBound(0); i++)
                { det *= matrix[i, i]; }

                return det;
            }

            public void mulMatrixVector(T[,] mat, T[] vec, T[] result)
            {
                for (int i = 0; i < vec.Length; i++)
                {
                    result[i] = default(T);
                    for (int j = 0; j < vec.Length; j++)
                    {
                        result[i] += (Number<T>)mat[i, j] * vec[j];
                    }
                }
            }

            public T matrixNorm(T[,] mat)
            {
                T nrm = default(T);
                for (int i = 0; i <= mat.GetUpperBound(0); i++)
                {
                    for (int j = 0; j <= mat.GetUpperBound(1); j++)
                    {
                        nrm += (Number<T>)mat[i, j] * mat[i, j];
                    }
                }

                return Number<T>.ConvertToNumber(System.Math.Sqrt(Number<T>.getDoubleValue(nrm)));
            }

            public T vectorNorm(T[] vec)
            {
                T nrm = default(T);
                for (int i = 0; i < vec.Length; i++)
                {
                    nrm += (Number<T>)vec[i] * vec[i];
                }

                return Number<T>.ConvertToNumber(System.Math.Sqrt(Number<T>.getDoubleValue(nrm)));
            }

            public void copyarray(T[] a_in, T[] a_out)
            {
                for (int i = 0; i < a_in.Length; i++)
                {
                    a_out[i] = a_in[i];
                }
            }

            public void truecopymatrix(T[,] m_from, out T[,] m_to)
            {
                m_to = new T[m_from.GetUpperBound(0) + 1, m_from.GetUpperBound(1) + 1];
                for (int i = 0; i <= m_from.GetUpperBound(0); i++)
                {
                    for (int j = 0; j <= m_from.GetUpperBound(1); j++)
                    {
                        m_to[i, j] = m_from[i, j];
                    }
                }
            }


            public void truecopyvector(T[] v_from, out T[] v_to)
            {
                v_to = new T[v_from.Length];
                for (int i = 0; i < v_from.Length; i++)
                {
                    v_to[i] = v_from[i];
                }
            }

            public double MaxLambda(T[,] mat)
            {
                double Lambda_p = 0, Lambda_n = 50;
                T[] z_next = new T[mat.GetUpperBound(0) + 1];
                T[] z_prev = new T[mat.GetUpperBound(0) + 1];

                for (int i = 0; i <= mat.GetUpperBound(0); i++)
                {
                    z_next[i] = Number<T>.ConvertToNumber(0);
                    z_prev[i] = Number<T>.ConvertToNumber(1);
                }

                // iteration
                while (System.Math.Abs(Lambda_n - Lambda_p) > 0.0001)
                {
                    Lambda_p = Lambda_n;
                    mulMatrixVector(mat, z_prev, z_next);
                    Lambda_n = Number<T>.getDoubleValue((Number<T>)vectorNorm(z_next) / vectorNorm(z_prev));
                    copyarray(z_next, z_prev);
                }

                return Lambda_n;
            }

            public T[,] matrixMult(T[,] left, T[,] right)
            {
                T[,] res = new T[left.GetUpperBound(0) + 1, left.GetUpperBound(0) + 1];

                for (int i = 0; i <= left.GetUpperBound(0); i++)
                {
                    for (int j = 0; j <= left.GetUpperBound(0); j++)
                    {
                        res[i, j] = default(T);
                        for (int k = 0; k <= left.GetUpperBound(0); k++)
                        {
                            res[i, j] += (Number<T>)left[i, k] * right[k, j];
                        }
                    }
                }

                return res;
            }

            public void transpose(T[,] mat)
            {
                T tmp = default(T);
                for (int i = 0; i <= mat.GetUpperBound(0); i++)
                {
                    for (int j = 0; j <= mat.GetUpperBound(0); j++)
                    {
                        tmp = mat[i, j];
                        mat[i, j] = mat[j, i];
                        mat[j, i] = tmp;
                    }
                }
            }

            public T trace(T[,] mat)
            {
                Number<T> tr = default(T);
                for (int i = 1; i <= mat.GetUpperBound(0); i++)
                {
                    tr += mat[i, i];
                }

                return tr;
            }
        }

        static public class ArrayOpsWrapper<T>
        {
            static public ArrayOps<T> arrayOperations = new ArrayOps<T>();
        }
    }
}
