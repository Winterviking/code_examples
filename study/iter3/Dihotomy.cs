using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    struct interval
    {
        double from;
        double to;
    }

    class Dihotomy
    {
        List<interval> intervals;
        List<double> root_x;

        void DihotomyProc( double [] xs,double [] ys )
        {
            
        }

        
        void RootLocalisation(double[] xs, double[] ys)
        {
            // if both share one side
            //0-random;1-inc;2-dec
            int p_state = 0;
            int n_state;
            // normal root
            bool m_root = false;
            // further
            bool l_root,r_root;
            
            for (int i = 1; i < xs.Length; i++)
            {
                
            }
        }
    }
}
