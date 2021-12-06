using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    namespace Math
    {
        class Matrix<T> : IParameters
        {
            public Matrix()
            { }
            public Matrix(T[,] initvalue)
            {
                Value = initvalue;
            }

            public Matrix(Matrix<T> toclone)
            {   
                // Full true copying
                T[,] res;

                truecopymatrix(toclone.Value, out res);
                this.matrix = res;
                this.square = toclone.Square;
            }

            public void SetParameter(object data, int additionalData = 0)
            {
                // Standart parameter passing, so we can adjust static methods to our needs easilly
                // these are enums mostly so its ok to call em w/o order))))
                Math.matrix.MatrixFunctionalFactory<T>.det.SetParameter(data,additionalData);
            }

            public T[,] Value
            {
                get
                {
                    return matrix;
                }
                set
                {
                    if (value.GetUpperBound(0) == value.GetUpperBound(1))
                    {
                        square = true;
                    }
                    matrix = value;
                }
            }

            void truecopymatrix( T[,] m_from, out T[,] m_to )
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

            public T[,] cloneValue()
            {
                T[,] res;
                truecopymatrix(matrix, out res);
                return res;
            }

            public Matrix<T> Clone ()
            {
                return new Matrix<T>(this);
            }

            public T Determinant( E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY )
            {
                return Math.matrix.MatrixFunctionalFactory<T>.det.calculate( matrix, keep );
            }

            public T Trace()
            {
                return Math.matrix.MatrixFunctionalFactory<T>.trace.calculate(matrix);
            }

            private T[,] matrix;
            private bool square;

            public bool Square
            {
                get
                {
                    return square;
                }
            }
        }
    }
}