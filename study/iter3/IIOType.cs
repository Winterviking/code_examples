using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    public interface IIOType<T>
    { 
        T ConsoleInput();
        T FileInput(string filename_ = null);
        T VariableInput();

        void ConsoleOutput( T obj );
        void FileOutput( T obj );
        void VariableOutput( T obj );

        void SetParam(object data, int additionalData = 0);

        string Filename
        {
            set;
        }
    }

    // TODO:: maby add intermediate interface between matrix and classified matrix aka : IOTYPE<t> -> MatrixIO<T> -> DoubleMatrixIOCode

    public class DoubleMatrixIOCode : IIOType<double[,]> // TODO :: work with Input registers ;)
    {
        public double[,] ConsoleInput()
        {
            double[,] res = null;
            return res;
        }
        public double[,] FileInput(string filename_ = null)
        {
            if (filename_ != null)
            { filename = filename_; }

            if (filename != null)
            {
                registers<double>.MatrixI = MatrixInput(SystemIO.OpenFile(filename));
            }
            else
            {
                SystemIO.Log("Error:: filename is not specified");
                registers<double>.MatrixI = null;
            }
            return registers<double>.MatrixI;
        }

        public double[,] VariableInput()
        {
            double[,] res = null;
            return res;
        }

        // input a matrix N x N from textchunk
        protected double[,] MatrixInput(string[] lines)
        {
            double[,] where;
            char[] charSeparators = { ' ' };
            int counter = -1;
            int i = 0;
            int sidelength = 0;
            // first line count sidelength
            string[] tmparr;
            do
            {
                counter++;
                tmparr = lines[counter].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
            }
            while (tmparr.Length == 0);

            sidelength = tmparr.Length;
            registers<double>.Sidelength = sidelength;
            registers<double>.initRegister(E_REGISTER_TYPE.MATRIX_IO);
            where = registers<double>.MatrixI;

            // main matrix read loop
            while (true)
            {
                for (int j = 0; j < sidelength; j++)
                {
                    try
                    {
                        where[i, j] = Convert.ToDouble(tmparr[j], System.Globalization.CultureInfo.InvariantCulture);
                    }
                    catch (System.FormatException)
                    {
                        //ERROR
                        SystemIO.Log("format xception");
                    }
                }

                i++;

                if (i + counter < lines.Length && i < sidelength)
                {
                    tmparr = lines[counter + i].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                }
                else //Error
                {
                    //                    sysio.Log("matrix format xception");
                    break;
                }
            }
            return where; 
        }

        public void SetParam(object data, int additionalData = 0)
        {
            if (data.GetType() == typeof(string))
            {
                filename = (string)data;
//                ready = true;
            }
        }

        public void ConsoleOutput(double[,] obj)
        {
            string blah;
            for (int i = 0; i < registers<double>.Sidelength; i++)
            {
                blah = "";
                for (int j = 0; j < registers<double>.Sidelength; j++)
                {
                    blah += obj[i, j].ToString() + " ";
                }
                SystemIO.Log(blah);
            }
        }
        public void FileOutput(double[,] obj)
        { }
        public void VariableOutput(double[,] obj)
        { }

        public string Filename
        {
            set
            {
                filename = value;
            }
        }

        private string filename = null;
    }

    // Static Wrapper for all the inputs
    namespace IO
    {
        static public class MatrixIO
        {
            static public IIOType<double[,]> Double = new DoubleMatrixIOCode();
        }
    }

/*    static public class IOType
    {
        public void Input( E_IO_TYPE type = E_IO_TYPE.FILE )
        {

            //Type F
            //if ( typeof(T).IsArray )
            //{
            //    F = typeof(T).GetElementType();
            //}
            //else
            //{
            //    F = typeof(T);
            //}

            //F.AssemblyQualifiedName m = new 

            //if (registers<RT>.MatrixI == null)
            //{ 

            //}

            switch( type )
            {
                case E_IO_TYPE.MANUAL:
                    {
//                        ManualInput(); //future
                    }
                    break;
                case E_IO_TYPE.FILE:
                    {
                        if ( ready )
                            FileInput();
                    }
                    break;
                case E_IO_TYPE.VARIABLE:
                    { 
                        // FUTURE
                    }
                    break;
            }
        }

//        abstract protected void ManualInput();
        abstract protected void FileInput();
//        abstract protected void VariableInput();

        public void Output( E_IO_TYPE type = E_IO_TYPE.MANUAL )
        {
            switch (type)
            {
                case E_IO_TYPE.MANUAL:
                    {
                        ManualOutput();
                    }
                    break;
                case E_IO_TYPE.FILE:
                    {
                        //FileOutput();
                    }
                    break;
                case E_IO_TYPE.VARIABLE:
                    {
                        //VariableOutput();
                    }
                    break;
            }
        }

        abstract protected void ManualOutput();
//        abstract protected void FileOutput();
//        abstract protected void VariableOutput();


        public void SetParam(object data, int additionalData = 0)
        {
            if (data.GetType() == typeof(string))
            {
                filename = (string)data;
                ready = true;
            }
        }

        protected static string filename;
        protected static bool ready = false;
    }*/

    //static public class MatrixIO : IOType
    //{
    //    void FileInput()
    //    {
    //        if (ready)
    //        {
    //            MatrixInput(SystemIO.OpenFile(IOType.filename));
    //        }
    //    }
    //}
}
