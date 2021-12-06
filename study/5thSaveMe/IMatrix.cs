using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    // matrix contract
    public interface IMatrix<T>
    {
        // RESULT is reference and must be initialized before
        // also there should be no fool - tests
        void mulVectorR_unsafe( ref IVector<T> argument, ref IVector<T> res );

        T[,] Value
        {
            get;
            set;
        }

        T[,] cloneValue(); // true cloning of value

        IMatrix<T> Clone(); // copy constructor

        T Determinant(Math.E_DETERMINANT_CALCULATION_METHOD method = Math.E_DETERMINANT_CALCULATION_METHOD.GAUSS, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY);

        T Trace();

        T MaxLambda
        {
            get;
        }

        List<T> EigenValues
        {
            get;
        }
        IVector<T>[] EigenVectors
        {
            get;
        }

        // file input : type specific : thats why its unsafe
        void InputFromFileUnsafe(string filename);

        // output
        void Dump();

        // MATRIX SPECIFIC
        List<T> CalculateEigenValues(E_CALCULATION_METHOD_EIGEN_VALUES method = E_CALCULATION_METHOD_EIGEN_VALUES.INTERPOLATION_OF_EIGEN_DETERMINANT_FUNCTION);

        bool Square
        {
            get;
        }

        T this[int x, int y]
        {
            get;
            set;
        }

        IVector<T>[] CalculateEigenVectors();

    } 
}
