using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{

    // move all methods into this class
    static public class ServiceMath<T>
    {

        // TEST DETERMINANT !!!!
        static public T determinant( T [,] matrix)// Gauss determinant
        {
            Number<T> coeff;

            for(int k=0; k < registers<T>.Sidelength; k++)
            {
                for (int i = k + 1; i < registers<T>.Sidelength; i++)
                {
			        if( Number<T>.CompareToZero(matrix[k,k]) )
                        {break;}
                    else
                        {coeff = Number<T>.negate( (Number<T>)matrix[i,k] / matrix[k,k] );}

                    for (int j = k; j < registers<T>.Sidelength; j++)
                        {matrix[i,j] += coeff * matrix[k,j];}
		        }
	        }

            Number<T> det = Number<T>.ConvertToNumber(1);
            for (int i = 0; i < registers<T>.Sidelength; i++)
                {det *= matrix[i,i];}

	        return det;
        }

        // TEST 

        // do i need it?
/*        public void copymatrix_clone( double[,] m_in, out double[,] m_out)
        {
            m_out = (double[,])m_in.Clone();
        }*/



        static public void copyarray(T[] a_in, T[] a_out)
        {
            for (int i = 0; i < registers<T>.Sidelength; i++)
            {
                a_out[i] = a_in[i];
            }
        }

        //static public void prepare_matrix( double [,] to_prep, double lambda )
        //{
        //    for (int i = 0; i < registers.Sidelength; i++)
        //    {
        //        to_prep[i, i] = to_prep[i, i] - lambda; 
        //    }
        //}

        // MAXLAMBDA!!!!
        static public double [,] matrixMult( double [,] left, double [,] right )
        {
            double [,] res = new double[registers<T>.Sidelength,registers<T>.Sidelength];

            for (int i = 0; i < registers<T>.Sidelength; i++)
	        {
		        for (int j = 0; j < registers<T>.Sidelength; j++)
		        {
                    res[i,j] = 0;
			        for (int k = 0; k < registers<T>.Sidelength; k++)
			        {
			            res[i,j] += left[i,k] * right[k,j];
			        }/
		        }
	        }

            return res;
        }

        static public void scaleMatrix ( T[,] mat, T coeff )
        {
            for (int i = 0; i < registers<T>.Sidelength; i++)
	        {
		        for (int j = 0; j < registers<T>.Sidelength; j++)
		        {
			         mat[i,j] *= (Number<T>)coeff;
		        }
	        }
        }

        static public void transpose ( T[,] mat )
        {
            T tmp = default(T);
            for (int i = 1; i <= registers<T>.Sidelength; i++)
            {
                for (int j = 1; j <= registers<T>.Sidelength; j++)
                {
                    tmp = mat[i,j];
                    mat[i,j]=mat[j,i];
                    mat[j,i] = tmp;
                }
            }
        }

        static public void mulMatrixVector(T[,] mat, T[] vec, T[] result)
        {
            for (int i = 0; i < registers<T>.Sidelength; i++)
            {
                result[i] = default(T);
                for (int j = 0; j < registers<T>.Sidelength; j++)
                {
                    result[i] += (Number<T>)mat[i, j] * vec[j];
                }
            }
        }



        static public double MaxLambda(T[,] mat)
        {
//            int n = 1000; // number of steps
            double Lambda_p = 0, Lambda_n = 50;
            T[] z_next = new T[registers<T>.Sidelength];
            T[] z_prev = new T[registers<T>.Sidelength];

            for (int i = 0; i < registers<T>.Sidelength; i++)
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

 //       public MemoryManager registers;
    }
}
