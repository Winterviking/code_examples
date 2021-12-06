using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public enum E_DIGITAL_SOLVE_METHOD
    { 
        DIHOTOMY
    }

    class Solver : ISolver<double>
    {
        public double Solve(DlgFunction<double> equation, double from, double to, E_DIGITAL_SOLVE_METHOD method)
        {
            double res = 0;
            if (method == E_DIGITAL_SOLVE_METHOD.DIHOTOMY)
            {
                double fmid, mid;
                do
                {
                    mid = from + (to - from) / 2;
                    fmid = equation(mid);

                    if (fmid == 0)
                    {
                        break;
                    }
                    else if (equation(from) * fmid < 0)
                    {
                        to = mid;
                    }
                    else if (equation(to) * fmid < 0)
                    {
                        from = mid;
                    }
                }
                while ( ((to - from) > 0.000000001 ) /*&& ( fmid > 0.1 )*/ );

                if (fmid != 0)
                {
                    mid = from + (from - to) / 2;
                }
                res = mid;
            }
            else
            {
                res = 0;
            }

            return res;
        }
    }
}
