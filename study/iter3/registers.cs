using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    public enum E_IO_TYPE
    {
        MANUAL,
        FILE,
        VARIABLE
    }

    public enum E_REGISTER_TYPE
    { 
        NUMBER,
        MATRIX,
        MATRIX_WORK,
        MATRIX_IO
    }

    static public class registers<T>
    {
        static public T[] Vector
        {
            get
            {
                if (vector == null)
                    { vector = new T[sidelength]; }
                return vector;
            }
            set
            {
                if (value != null)
                {
                    if (value.Length == sidelength)
                        { vector = value; }
                    else
                        { vector = null; }
                }
                else
                    { vector = null; }
            }
        }
        static public T[] VectorW
        {
            get
            {
                if (vectorW == null)
                { vectorW = new T[sidelength]; }
                return vectorW;
            }
            set
            {
                if (value != null)
                {
                    if (value.Length == sidelength)
                    { vectorW = value; }
                    else
                    { vectorW = null; }
                }
                else
                { vectorW = null; }
            }
        }

        static private T[] vector;
        static private T[] vectorW;

        static public T[,] Matrix
        {
            get
            {
                if (matrix == null)
                    { matrix = new T[sidelength,sidelength]; }
                return matrix;
            }
            set
            {
                if (value != null)
                {
                    if ((value.GetUpperBound(0) == (sidelength - 1)) && (value.GetUpperBound(1) == (sidelength - 1)))
                    { matrix = value; }
                    else
                    { matrix = null; }
                }
                else
                { matrix = null; }
            }
        }
        static public T[,] MatrixW
        {
            get
            {
                if (matrixW == null)
                { matrixW = new T[sidelength, sidelength]; }
                return matrixW;
            }
            set
            {
                if (value != null)
                {
                    if ((value.GetUpperBound(0) == (sidelength - 1)) && (value.GetUpperBound(1) == (sidelength - 1)))
                    { matrixW = value; }
                    else
                    { matrixW = null; }
                }
                else
                { matrixW = null; }
            }
        }
        static public T[,] MatrixI
        {
            get
            {
//                if (matrixI == null)
//                /*{*/ matrixI = new T[sidelength, sidelength]; /*}*/
                if (matrixI == null)
                {
                    //switch (itype)
                    //{
                    //    case E_IO_TYPE.FILE:
                    //        {
                    //            matrixI = IO.MatrixIO.FileInput();

                    //        }
                    //        break;
                    //    case E_IO_TYPE.MANUAL:
                    //        { }
                    //        break;
                    //    case E_IO_TYPE.VARIABLE:
                    //        { }
                    //        break;
                    //}
                }
                return matrixI;
            }
            set
            {
                if (value != null)
                {
                    if ((value.GetUpperBound(0) == (sidelength - 1)) && (value.GetUpperBound(1) == (sidelength - 1)))
                    { matrixI = value; }
                    else
                    { matrixI = null; }
                }
                else
                { matrixI = null; }
            }
        }

        static private T[,] matrix;
        static private T[,] matrixW;
        static private T[,] matrixI;

        static public void initRegister( E_REGISTER_TYPE type )
        {
            switch (type)
            {
                case E_REGISTER_TYPE.MATRIX_IO:
                    {
                        matrixI = new T[sidelength, sidelength];
                    }
                    break;
            }
        }

        // Dunno y i need em, but w/e
        static public T number;
        static public T numberW;

        static public int Sidelength
        {
            get
                { return sidelength; }
            set
            {
                if (value > 0)
                {
                    sidelength = value;
                }
                else
                {
                    sidelength = 0;
                }
            }
        }

        static private int sidelength;



        // TODO:::: One day check possibility to run static T-specific input over I registers : that seems to be handy lel
        static public E_IO_TYPE InputDefaultType
        {
            set
            { 
                itype = value;
            }

            get
            { return itype; }
        }
        static public E_IO_TYPE OutputDefaultType
        {
            set
            {
                otype = value;
            }

            get
            { return otype; }
        }

        static private E_IO_TYPE itype = E_IO_TYPE.FILE;
        static private E_IO_TYPE otype = E_IO_TYPE.MANUAL;
        // TODO:::: FUTURE STRUCTURE
        //T[] vectorI;
        //T[] vectorO;
        //T[] vectorL;
        //T[] vectorR;
        //T[] vectorWL;
        //T[] vectorWR;
        //T[] vectorRes;
        //T[,] matrixL;
        //T[,] matrixR;
        //T[,] matrixWL;
        //T[,] matrixWR;
        //T[,] matrixRes;
        //T[,] matrixI;
        //T[,] matrixO;
        //T numberI;
        //T numberO;
        //T numberL;
        //T numberR;
        //T numberWL;
        //T numberWR;
        //T numberRes;
    }
}
