using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
    class scriptInterpreter
    {
        public void Initialize( Console console_ ) 
        {
            console = console_;
            reg = new register();
            charSeparators = new char[] { ' ' };// legit lol
            forceautoinit = true;
            expectnextlineinputmatrix = false;
            forceleftregisterroute = true;
            expectnextlineinputvector = false;
            multilinemode = false;
        }

        // INTERFACE CONNECTION
        public void interpreteLine(ref string str_)
        {
            str = str_;
            string[] words = str.Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
            interpreteLine(ref words);
        }

        // interprete one line 
        public void interpreteLine( ref string [] words )
        {
//            str = str_;
//            words = str.Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);

            if (words[0] == "run")// first levl interpretation
            {
                multilinemode = true;
                string[] rows = System.IO.File.ReadAllLines(words[1]);
                string[] tmparr;
                int from = 0;
                do
                {
                    tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                    while (tmparr.Length == 0)
                    {
                        from++;
                        tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                    }
                    

                    if ( expectnextlineinputmatrix )
                    {
                        // input init
                        if (forceautoinit && ( tmparr.Length != reg.sidelength ))
                        {
                            reg.sidelength = tmparr.Length;
                            reg.reinit_registers();
                        }
                        // matrix input
                        if ( forceleftregisterroute )
                            {inputFromTextChunkDMatrix(ref rows, ref from, ref reg.ldmatrix, ref tmparr);}
                        else
                            {inputFromTextChunkDMatrix(ref rows, ref from, ref reg.dmatrixin, ref tmparr);}
                        
                        expectnextlineinputmatrix = false;
                        runExtension(extensionnum);
                    }
                    else if ( expectnextlineinputvector )
                    {
                        
                    }
                    else
                    {
                        interpreteLine(ref tmparr);
                    }
                    from++;
                }
                while (rows.Length != from);
            }
            else if (words[0] == "init")
            {
                if (words[1] == "auto")
                {
                    if ( words[2] == "true" )
                        {forceautoinit = true;}
                    else if ( words[2] == "false" )
                        {forceautoinit = false;}
                }
                else if (words[1] == "length")
                {
                    if ( !forceautoinit )
                    {
                        reg.sidelength = Convert.ToInt32(words[2]);
                        reg.resetRegisters();
                    }
                }
            }
            else if (words[0] == "find" )
            {
                // WILL BE EXTENSIONS via INTERFACE classes
                if (words[1] == "eigenvalues")
                {
                    if (words.Length > 2) 
                    {
                        if ( forceleftregisterroute )
                            {inputFromFileDMatrixLR(ref words[2]);}
                        else
                            {inputFromFileDMatrixIN(ref words[2]);}
                        extensionnum = 1;
                        runExtension(extensionnum);
                    }
                    else if (multilinemode)
                    {
                        expectnextlineinputmatrix = true;
                        extensionnum = 1;
                    }
                    else
                    {
                        console.consoleWindow.AppendText("errroooor");
                    }
                    extensionnum = 1;
                }
            }
            else if (words[0] == "setivar")
            {
                if (words[1] == "double")
                {
                    // or some trim work maybe
                    if (words[2] == "array1d")
                    {
                        if (words[3] == "id")
                        {
                            int id = Convert.ToInt32(words[4]);
                            if (words[5] == "length")
                            {
                                // DANGEROUS :: all parts, where these arrays are used must be updated, so arrays will be garbage collected
                                if (id == 1)
                                {
                                    // dropping all the possible references
                                    reg.darray_reg_one = null;
                                    reg.darray_reg_one = new double[Convert.ToInt32(words[6])];
                                }
                                else if (id == 2) // same as 1 : will be redone with real memory management machine  lol : heres just a demo
                                {
                                    reg.darray_reg_two = null;
                                    reg.darray_reg_two = new double[Convert.ToInt32(words[6])];
                                }
                            }
                        }
                    }
                }
                else if (words[1] == "int")
                {

                }
            }
        }

        void inputFromTextChunkDMatrix(ref string[] rows_, ref int from, ref double[,] where, ref string[] firstline)
        { 
            string[] tmparr;

            for (int i = 0; i < reg.sidelength; i++)
            {
                if (i == 0)
                    {tmparr = firstline;}
                else
                    {tmparr = rows_[i + from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);}
                for (int j = 0; j < reg.sidelength; j++)
                {
                    where[i, j] = Convert.ToDouble(tmparr[j], System.Globalization.CultureInfo.InvariantCulture);
                    console.consoleWindow.AppendText(where[i, j].ToString() + ' ');
                }
                console.consoleWindow.AppendText("\n");
            }
            from += reg.sidelength - 1;
        }

        void inputFromFileDMatrix(ref string filename, ref double[,] where)
        {
            string[] rows = System.IO.File.ReadAllLines(filename);
            string[] tmparr;
            int from = -1;

            do
            {
                from++;
                tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                console.consoleWindow.AppendText(tmparr.Length.ToString() + ' ');
            }
            while (tmparr.Length == 0);

            if ((tmparr.Length != reg.sidelength) && forceautoinit)
            {
                reg.sidelength = tmparr.Length;
                reg.reinit_registers();
            }

            inputFromTextChunkDMatrix(ref rows, ref from, ref where, ref tmparr);

        }

        void inputFromFileDMatrixLR ( ref string filename )
        {
            inputFromFileDMatrix(ref filename, ref reg.ldmatrix);
        }
        void inputFromFileDMatrixIN ( ref string filename )
        {
            inputFromFileDMatrix(ref filename, ref reg.dmatrixin);
        }

        void runExtension( int num )
        {
            if (num == 1)
            {
                // eigenvalue extension run()
                // TODO:: implement OOP approach to extensions
                eigenvalue egv = new eigenvalue();
                egv.eigenProc(ref reg);

                for (int i = 0; i < reg.x.Count; i++)
                {
                    console.consoleWindow.AppendText(reg.x[i].ToString() + " " + reg.y[i].ToString() + "\n");
                }
            }
        }
        
        
        char[] charSeparators;

        // internal buffers
        string str;

        bool forceautoinit;
        bool expectnextlineinputmatrix;
        bool expectnextlineinputvector;
        bool forceleftregisterroute;
        bool multilinemode;

        int extensionnum;

        register reg;
        Console console;
    }
}
