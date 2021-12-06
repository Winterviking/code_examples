using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    class SimpleReverseVectorIterativeProcess : AVectorIterativeProc<double>
    {
        public SimpleReverseVectorIterativeProcess( E_SLAE_SOLVE_METHOD method = E_SLAE_SOLVE_METHOD.GAUSS)
        {
            method = E_SLAE_SOLVE_METHOD.GAUSS;
            solver = new StandartSLAESolver();
        }

        public override IVector<double> Iteration(IVector<double> prev)
        {
            //sadface
            SLAE<double> slae = new SLAE<double>();

            slae.coefficients = operator_;
            slae.rightColumn = prev.Clone();
            IVector<double> res = new DVector(solver.Solve(slae, E_SLAE_SOLVE_METHOD.GAUSS, E_RELATION_OPERATOR_DATA.CORRUPTION));

            return res;
        }

        public override IVector<double> Proc(double epsilon, int maxnumber = 10000000)
        { 
            for (int j = 0; j < number_; j++)
			{
			    prev_[j] = 10;
			}
            SLAE<double> slae = new SLAE<double>();

            int i = 0;

            do
            {
                slae.coefficients = operator_.Clone();
                Math.ArrayOpsWrapper<double>.arrayOperations.copyarray(prev_.Value,next_.Value);
                slae.rightColumn = next_;

                next_ = new DVector( solver.Solve(slae,method,E_RELATION_OPERATOR_DATA.CORRUPTION) );

                prev_.minus(ref next_, ref error_);
                holder_ = prev_;
                prev_ = next_;
                next_ = holder_;
                i++;
            }
            while( i < maxnumber && error_.norm() > epsilon );

            return prev_;
        }

        public override IMatrix<double> Operator
        {
            set
            {
                operator_ = value;
                if (number_ != (operator_.Value.GetUpperBound(0) + 1))
                {
                    number_ = operator_.Value.GetUpperBound(0) + 1;
                    error_ = new DVector(new double[number_]);
                    prev_ = new DVector(new double[number_]);
                    next_ = new DVector(new double[number_]);
                }
            }
        }

        IVector<double> prev_ = null;
        IVector<double> next_ = null;
        IVector<double> error_ = null;
        IVector<double> holder_ = null;
        int number_;
        E_SLAE_SOLVE_METHOD method;
        ISLAESolver<double> solver;
    }
}
