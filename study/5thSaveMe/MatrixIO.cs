using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _5thSaveMe.Math;

namespace _5thSaveMe
{
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

            double[,] res = null;

            if (filename != null)
            {
                res = MatrixInput(SystemIO.OpenFile(filename));
            }
            else
            {
                SystemIO.Log("Error:: filename is not specified");
            }
            return res;
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

            where = new double[sidelength, sidelength];

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
            for (int i = 0; i <= obj.GetUpperBound(0); i++)
            {
                blah = "";
                for (int j = 0; j <= obj.GetUpperBound(0); j++)
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

}