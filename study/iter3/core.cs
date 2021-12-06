#define SAD_DEBUG

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    class core
    {
        public core( System.Windows.Forms.RichTextBox console )
        {
            SystemIO.initDefaultConsole(console);
//            sm.mm = mm;
//            initSysIO( console );
        }

//        DataSource lg = new Lagrange();
//        ServiceMath sm = new ServiceMath();
//        public SystemIO sysio = null;
//        public MemoryManager mm = new MemoryManager();

//        bool console_init_flag = false;
        
        public void Run()
        {
            IFunction<double, double> lg = new LagrangeInterpolator();

            double[,] mat = IO.MatrixIO.Double.FileInput("matrix.txt");
            double maxlambda = ServiceMath<double>.MaxLambda(mat);
            SystemIO.Log("MaxLambda - " + maxlambda.ToString());
            lg.SetParameter( -maxlambda - 1, 1);
            lg.SetParameter( maxlambda + 1, 2);

            IFunction<double,double> wurk = new EigenDeterminant<double>();
            wurk.SetParameter(mat);
            lg.SetParameter((IFunction<double, double>)wurk, 100);// function
            lg.SetParameter(80, 10);// number
            lg.SetParameter(E_GRID_TYPE.CHEBYSHEV);
            IDataProvider<double> wurkp = new FunctionDataProvider();
            wurkp.SetParameter((IFunction<double, double>)lg, 100);
            wurkp.SetParameter( -maxlambda - 1, 1);
            wurkp.SetParameter(maxlambda + 1, 2);
            double [,] points = wurkp.getAllPoints(1000);

            for (int i = 0; i < 1000; i++)
            {
                SystemIO.Log(points[i,0].ToString() + " " + points[i,1].ToString());
            }
            











/*            Function func = new EigenDeterminant();
            func.adjustSettings("matrix.txt");
            matrixOutput(registers.Matrix);
            lg.ito = ServiceMath<double>.MaxLambda(registers.Matrix) + 1;
            SystemIO.Log("Lambda = " + (lg.ito - 1).ToString());
            lg.ifrom = - lg.ito;
            lg.function = func;
            lg.setParam(E_GRID_TYPE.CHEBYSHEV);
            lg.setParam(128);

            lg.generateAllPoints(1000);

            // DEBUG!!!!!
            for (int i = 0; i < 1000; i++)
            {
                SystemIO.Log(lg.Array_x[i].ToString() + " " + lg.Array_y[i].ToString());
            }
            */


            //// matrix input
            //mm.matrix = MatrixInput(sysio.OpenFile("matrix.txt"));

            //// highest eigenvalue
            //lg.to_ = sm.MaxLambda(mat) + 1;
            //lg.from_ = - lg.to_;
            //lg.generateGrid(E_GRID_TYPE.CHEBYSHEV, 22);

            //sm.copymatrix_clone( mm.matrix, out mm.wmatrix );
            //sm.prepare_matrix(mm.wmatrix, lg.array_x[i]);
            //sm.determinant(mm.wmatrix);
 
            //for (int i = 1; i < lg.number; i++)
            //{
            //    sm.copymatrix(mm.matrix, mm.wmatrix);
            //    sm.prepare_matrix(mm.wmatrix, lg.array_x[i]);
            //    lg.array_y[i] = sm.determinant( mm.wmatrix );
            //}

            //lg.InterpolateAllPoints(10000);

        }

/*        public double [,] MatrixInput( string [] lines )
        {
            double [,] where;
            char[] charSeparators = {' '};
            int counter = -1;
            int i = 0;
            int sidelength = 0;
            // first line count sidelength
            string[] tmparr;
            do
            {
                counter++;
                tmparr = lines[counter].Split( charSeparators, StringSplitOptions.RemoveEmptyEntries );
            }
            while( tmparr.Length == 0 );

            sidelength = tmparr.Length;
            mm.sidelength = sidelength;
            where = new double[sidelength,sidelength];
                    
            // main matrix read loop
            while( true )
            {
                for (int j = 0; j < sidelength; j++)
                {
                    try
                    {
                        where[i, j] = Convert.ToDouble(tmparr[j], System.Globalization.CultureInfo.InvariantCulture);
                    }
                    catch ( System.FormatException )
                    {
                        //ERROR
                        if (console_init_flag)
                        {
                            sysio.Log("format xception");
                        }
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
        }*/
/*
        public void matrixOutput(double[,] what)
        {
            string blah;
            for (int i = 0; i < registers.Sidelength; i++)
            {
                blah = "";
                for (int j = 0; j < registers.Sidelength; j++)
                {
                    blah += what[i, j].ToString() + " ";
                }
                SystemIO.Log(blah);
            }
        }*/

        //public void initSysIO ( System.Windows.Forms.RichTextBox rtbox )
        //{
        //    sysio = new SystemIO();
        //    if (rtbox != null)
        //    {
        //        sysio.console = rtbox;
        //        console_init_flag = true;
        //    }
        //}

    }
}
