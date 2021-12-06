using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// TODO:::: Add bool flag CHANGED : to make sure that all on-demand data will be cleaned after changing underlying array
// TODO:::: Control function availability if matrix is not squared
// TODO:::: Determinant : inside gauss solver : utilize it

namespace _5thSaveMe
{
    public enum E_CALCULATION_METHOD_EIGEN_VALUES
    {
        INTERPOLATION_OF_EIGEN_DETERMINANT_FUNCTION
    }

    public class DMatrix : IMatrix<double>
    {
        public DMatrix()
        { }
        public DMatrix(double[,] initvalue)
        {
            Value = initvalue;
        }

        public DMatrix(IMatrix<double> toclone)
        {
            // Full true copying
            double[,] res;

            Math.ArrayOpsWrapper<double>.arrayOperations.truecopymatrix(toclone.Value, out res);
            this.matrix = res;
            this.square = toclone.Square;
        }

        public void mulVectorR_unsafe( ref IVector<double> argument, ref IVector<double> res )
        {
            Math.ArrayOpsWrapper<double>.arrayOperations.mulMatrixVector(matrix, argument.Value, res.Value);
        }

        public double[,] Value
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

        public double[,] cloneValue()
        {
            double[,] res;
            Math.ArrayOpsWrapper<double>.arrayOperations.truecopymatrix(matrix, out res);
            return res;
        }

        public IMatrix<double> Clone()
        {
            return new DMatrix(this);
        }

        public double Determinant(Math.E_DETERMINANT_CALCULATION_METHOD method = Math.E_DETERMINANT_CALCULATION_METHOD.GAUSS, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY)
        {
            return Math.ArrayOpsWrapper<double>.arrayOperations.Determinant(matrix, method, keep);
        }

        public double Trace()
        {
            return Math.ArrayOpsWrapper<double>.arrayOperations.trace(matrix);
        }

        public double MaxLambda
        {
            get
            {
                if (maxLambda_ == null)
                {
                    maxLambda_ = Math.ArrayOpsWrapper<double>.arrayOperations.MaxLambda(matrix);
                }
                return maxLambda_.Value;
            }
        }

        public void InputFromFileUnsafe(string filename)
        {
            // LOLZ
            matrix = IO.MatrixIO.Double.FileInput(filename);
        }

        public void Dump()
        {
            IO.MatrixIO.Double.ConsoleOutput(matrix);
        }

        // MATRIX SPECIFIC
        public List<double> CalculateEigenValues(E_CALCULATION_METHOD_EIGEN_VALUES method = E_CALCULATION_METHOD_EIGEN_VALUES.INTERPOLATION_OF_EIGEN_DETERMINANT_FUNCTION)
        {
            if (method == E_CALCULATION_METHOD_EIGEN_VALUES.INTERPOLATION_OF_EIGEN_DETERMINANT_FUNCTION)
            {
                // maxlambda out
//                SystemIO.Log("MaxLambda : " + (MaxLambda).ToString());

                // grid generator : 1 for all the actions
                IGridGenerator1D<double> gg = new StandartGridGenerator(-MaxLambda - 1, MaxLambda + 1);

                // creating lagrange interpolator for hard-calculated gauss determinant function
                IFunction<double> func = new Math.ExtServices.EigenDeterminant<double>(this);
                IFunction<double> lg = new Lagrange(-MaxLambda - 1, MaxLambda + 1, 80, func, gg);

                // root finding from interpolation function utilizing functions of DigitalFunction class
                IDigitalFunction<double> digFunc = new DigitalFunction(lg, -MaxLambda - 1, MaxLambda + 1, 20000, gg);
                eigenValues_ = digFunc.FindRoots();

                // VERIFICATION LEL
                // DEBUG:::::
                SystemIO.Log("VERIFICATION EIGEN VALUES::::");
                SystemIO.Log("Number of eigen values : " + eigenValues_.Count.ToString());
                SystemIO.Log("MaxLambda : " + MaxLambda.ToString());
                for (int i = 0; i < eigenValues_.Count; i++)
                {
                    SystemIO.Log(eigenValues_[i].ToString());
                    SystemIO.Log("error :" + func.Function(eigenValues_[i]).ToString());
                }
                // U GUYS SUCK : GET SOME!!!!!
            }

            return eigenValues_;
        }

        // TODO :::: rewrite as iterative according to gheyarshinoff
        public IVector<double>[] CalculateEigenVectors()
        {
            if ( eigenValues_ == null )
            {
                CalculateEigenValues();
            }
            IVector<double>[] res = new IVector<double>[eigenValues_.Count];

 //           SLAE<double> slae = new SLAE<double>();
            IMatrix<double> smatrix = null;

            int sidelen = eigenValues_.Count;

 //           ISLAESolver<double> solver = new StandartSLAESolver();
            AVectorIterativeProc<double> vectorIterator = new SimpleReverseVectorIterativeProcess();

 //           slae.rightColumn = new DVector(new double[sidelen]);

            for (int i = 0; i < eigenValues_.Count; i++)
            {
                smatrix = this.Clone();
                for (int j = 0; j < sidelen; j++)
			    {
                    smatrix[j, j] -= eigenValues_[i];
                }

                vectorIterator.Operator = smatrix;

                res[i] = new DVector(vectorIterator.Proc(0.1,10));
                double norm = Math.ArrayOpsWrapper<double>.arrayOperations.vectorNorm(res[i].Value);
                for (int j = 0; j < sidelen; j++)
                {
                    res[i][j] /= norm;
                }
            }
            eigenVectors_ = res;
            return res;
        }

        public IVector<double>[] EigenVectors
        {
            get
            {
                if (eigenVectors_ == null)
                {
                    CalculateEigenVectors();
                }
                return eigenVectors_;
            }
        }

        public List<double> EigenValues
        {
            get
            {
                if (eigenValues_ == null)
                {
                    CalculateEigenValues(eigen_values_method);
                }
                return eigenValues_;
            }
        }

        private double[,] matrix;
        private bool square;
        
        private double? maxLambda_ = null;
        private List<double> eigenValues_ = null;
        private IVector<double>[] eigenVectors_ = null; 

        // DEFAULT METHODS
        E_CALCULATION_METHOD_EIGEN_VALUES eigen_values_method = E_CALCULATION_METHOD_EIGEN_VALUES.INTERPOLATION_OF_EIGEN_DETERMINANT_FUNCTION;
        E_SLAE_SOLVE_METHOD eigen_vectors_method = E_SLAE_SOLVE_METHOD.GAUSS;

        public bool Square
        {
            get
            {
                return square;
            }
        }

        public double this[int x, int y]
        {
            get { return matrix[x, y]; }
            set { matrix[x, y] = value; }
        }
    }
}
