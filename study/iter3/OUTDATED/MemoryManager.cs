/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// OUTDATED
 

namespace _5th_just_prog
{
    static public class registers_
    {
        private static void resetRegisters()
        {
            matrix = null;
            wmatrix = null;
        }
        // static registers
        static public double[,] Matrix
        {
            get
            {
                if (matrix == null)
                    { matrix = new double[sidelength,sidelength]; }
                return matrix; 
            }
            set 
            {
                int swag = value.GetUpperBound(0);
                if (sidelength == ( value.GetUpperBound(0) + 1 ) && sidelength == ( value.GetUpperBound(1) + 1 ))
                {
                    matrix = value;
                }
                else
                {
                    matrix = null;
                }
            }
        }
        static public double[,] WMatrix
        {
            get
            {
                if (wmatrix == null)
                { wmatrix = new double[sidelength, sidelength]; }
                return wmatrix;
            }
            set
            {
                if (sidelength == value.GetUpperBound(0) && sidelength == value.GetUpperBound(1))
                {
                    wmatrix = value;
                }
                else
                {
                    matrix = null;
                }
            }
        }
//        public double[] coeffitient;
//        public double[] roots;
//        public double[] points;
//        public double[] interpolationPoints;
//        public List<double> points;
//        public List<double> accum;
        static public int Sidelength
        {
            get
            { return sidelength; }
            set
            {
                if (value > 0)
                {
                    if (value != sidelength)
                    {
                        resetRegisters();
                        sidelength = value;
                    }
                }
                else
                {
                    SystemIO.Log("ERROR");
                }
            }
        }

        private static int sidelength;
        private static double[,] matrix;
        private static double[,] wmatrix;
    }
}
*/