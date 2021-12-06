using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public class SimpleMatrixOperatorVectorIterativeProcess : AVectorIterativeProc<double>
    {
        public SimpleMatrixOperatorVectorIterativeProcess(IMatrix<double> oper)
        {
            operator_ = oper;
            number_ = oper.Value.GetUpperBound(0) + 1;
            next_ = new DVector(new double[number_]);
            error_ = new DVector(new double[number_]);
            prev_ = new DVector(new double[number_]);
        }

        public override IVector<double> Iteration(IVector<double> prev)
        {
            operator_.mulVectorR_unsafe(ref prev,ref next_);
            for (int i = 0; i < prev.Value.Length; i++)
            {
                prev[i] = next_[i];
            }
            return prev;
        }

        public override IVector<double> Proc(double epsilon, int maxnumber = 10000)
        { 
            for (int j = 0; j < number_; j++)
			{
			    prev_[j] = 1;
			}

            int i = 0;

            do
            {
                operator_.mulVectorR_unsafe(ref prev_, ref next_);
                prev_.minus(ref next_, ref error_);
            }
            while( i < maxnumber || error_.norm() > epsilon );

            return next_;
        }

        IVector<double> prev_ = null;
        IVector<double> next_ = null;
        IVector<double> error_ = null;
        IVector<double> holder_ = null;
        int number_;
    }
}
