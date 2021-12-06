/*using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// OUTDATED

namespace _5th_just_prog
{
    namespace input
    {
        interface InputProc
        {
            object Input();
            void SetParam(object data, int additionalData = 0);
        }

        public class MatrixInputProc : InputProc 
        {
            public void SetParam(object data, int additionalData = 0)
            {
                if (data.GetType() == typeof(string))
                {
                    filename = (string)data;
                    ready = true;
                }
            }

            public object Input()
            {
                if (ready)
                {
                    return MatrixInput(SystemIO.OpenFile(filename));
                }
                else
                {
                    return null;
                }
            }

            // input a matrix N x N from textchunk
            public double[,] MatrixInput(string[] lines)
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

            bool ready = false;
            string filename;
        }

        class MatrixInput
        {
            static public double[,] getMatrixFromFile(string filename)
            {
                conductor.SetParam(filename);
                return (double[,])conductor.Input();
            }

            private static InputProc conductor = (InputProc) new MatrixInputProc();
        }
    }
}
*/