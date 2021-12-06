/*using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// OUTDATED

namespace _5th_just_prog
{
    interface Function
    {
        void getYbyX(double x, out double y);
        void adjustSettings(object data, int additionalData = 0);// if function got any parameters, u can set em through this function
    }

    public class EigenDeterminant : Function // TODO:: CUT DOWN LINES
    {
        public void getYbyX(double x, out double y)
        {
            // determinant calculation
            adjustSettings(x, 1);// prepare matrix
            y = ServiceMath<double>.determinant(registers.WMatrix);
        }

        public void adjustSettings(object data, int additionalData = 0) 
        {
            if (data.GetType() == typeof(string))
            {
                filename = (string)data;
                matrix = input.MatrixInput.getMatrixFromFile(filename);
                matrix_is_on = true;
                registers.Matrix = matrix;
                
            }
            else if (data.GetType() == typeof(double[,]))
            {
                matrix = (double[,])data;
                registers.Matrix = matrix;

                if (registers.Matrix != null)
                {
                    matrix_is_on = true;
                }
            }
            else if (data.GetType() == typeof(double) || additionalData == 1)
            { 
                if ( matrix_is_on )
                {
                    ServiceMath<double>.copymatrix(matrix, registers.WMatrix);
                    for (int i = 0; i < registers.Sidelength; i++)
                    {
                        registers.WMatrix[i, i] -= (double)data;
                    }
                }
            }
        }

        string filename;
        double[,] matrix;
        //states
        bool matrix_is_on = false;

    }

    // maby an static wrapper
}
*/