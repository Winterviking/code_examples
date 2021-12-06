using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
namespace roots
{
    class dihotomy
    {
        public void init(ref register reg_, double from_, double to_, ref interpolation.Lagrange lagrange_ )
        {
            dfrom = from_;
            dto = to_;
            reg = reg_;
            lagrange = lagrange_;

            precision = 0.0001;
            searchprecision = 0.1;

            intervals = new List<int>();
            suspicious = new List<int>();
            roots = new List<double>();
        }
        void RootLocalization( ref double[] y, double step)
        {
            intervals.Clear();
            suspicious.Clear();
            roots.Clear();

            int growing = 10, newgrowing = 10;// -1 0 1 make sense
            if ( y[0] == 0 )
            {
                roots.Add(dfrom);
            }
            for (int i = 1; i < y.Length; i++)
            {
                if ( y[i] == y[i - 1] )
                {
                    newgrowing = 0;
                    suspicious.Add(i);
                }
                else
                {
                    if (y[i] > y[i - 1])
                        {newgrowing = 1;}
                    else if (y[i] < y[i - 1])
                        {newgrowing = -1;}

                    if (y[i] * y[i - 1] < 0)
                        {intervals.Add(i);}
                    else
                    {
                        if ((growing <= 1) && (growing >= -1))
                        {
                            if (growing * newgrowing < 0)
                            {
                                suspicious.Add(i);
                            }
                        }
                    }
                }
                growing = newgrowing;
            }

/*
 *          bool growing = false;
            if (y[0] > y[1])
            {
                growing = false;
            }
            else if ( y[0] < y[1] )
            {
                growing = true;
            }

            if (y[0] == 0)
            {
                roots.Add(0);
            }
            for (int i = 1; i < y.Length; i++)
            {
                if (y[i] == 0)
                {
                    roots.Add(i*step + dfrom);
                } 
                else
                {
                    if (y[i] > y[i - 1])
                    {
                        if (!growing && (y[i] * y[i - 1] > 0) && ( i != 1 ) )
                        {
                            suspicious.Add(i);
                        }
                        growing = true;
                    }
                    else if (y[i] < y[i - 1])
                    {
                        if (growing && (y[i] * y[i - 1] > 0) && ( i != 1 ) )
                        {
                            suspicious.Add(i);
                        }
                        growing = false;
                    }
                    else if ( y[i] == y[i - 1] )
                    {
                        suspicious.Add(i);
                    }

                    if (y[i] * y[i - 1] < 0)
                    {
                        intervals.Add(i - 1);
                    }
                }
            }*/
        }

        public void dihotomyProc( ref double[] y, double step )
        {
            //100% root
            RootLocalization(ref y, step);
            double from, to, mid, midy = 0;
            // direct roots

            for (int i = 0; i < intervals.Count; i++)
            {
                from = ( intervals[i] - 1 )*step + dfrom;
                to = intervals[i]*step +dfrom;
//                from = y[intervals[i]];
//                to = y[intervals[i]-1];
                bool rootfound = false;

                do
                {
                    mid = from + (to - from) / 2;
                    lagrange.InterpolatePoint(mid, ref midy);
                    if ( midy == 0 )
                    {
                        roots.Add(mid);
                        rootfound = true;
                        break;
                    }
                    else if (midy * y[intervals[i]-1] < 0)
                    {
                        to = mid;
                    }
                    else if (midy * y[intervals[i]] < 0 )
                    {
                        from = mid;
                    }
                }
                while (from - to > precision);
                if (!rootfound)
                {
                    roots.Add(from + (to - from)/2);
                }
            }

            double diff;
            for (int i = 0; i < suspicious.Count; i++)
            {
                if (y[suspicious[i]] == y[suspicious[i] - 1])
                {
                    from = dfrom + (suspicious[i] - 1) * step;
                    to = dfrom + suspicious[i] * step;
                }
                else
                {
                    from = dfrom + (suspicious[i] - 2) * step;
                    to = dfrom + suspicious[i] * step;
                }

                int maxstep = 100;
                double betterstep = ( to - from ) / 100;
                double y1 = 0, y2 = 0;
                for (int j = 1; j < maxstep; j++)
                {
                    lagrange.InterpolatePoint(from + (j - 1) * betterstep, ref y1);
                    lagrange.InterpolatePoint(from + (j) * betterstep, ref y2);
                    diff = (y2 - y1) / betterstep;
                    if ( ( Math.Abs ( diff ) < precision ) && ( Math.Abs( ( y1 + y2 )/2 ) < precision ) )
                    {
                        roots.Add(from + (j - 0.5) * betterstep);
                    }
                }
            }

            for (int i = 0; i < roots.Count; i++)
            {
                reg.x.Add(roots[i]);
                double y_ = 0;
                lagrange.InterpolatePoint(roots[i], ref y_);
                reg.y.Add(y_);
            }
        }

        double precision;
        double searchprecision;

        List<int> intervals;
        List<int> suspicious;
        List<double> roots;

        interpolation.Lagrange lagrange;

        double dfrom;
        double dto;
        register reg;
    }
}
}