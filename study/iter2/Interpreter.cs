using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using _5th2nd.core;
using _5th2nd.Extensions;

namespace _5th2nd
{
/*    struct stacks_
    {
        public stacks_()
        {
            dlistl = new List<double>();
            dlistr = new List<double>();
            dx = new List<double>();
            dy = new List<double>();
        }
        public List<double> dlistl;
        public List<double> dlistr;
        public List<double> dx;
        public List<double> dy;
    };

    struct registers_
    {
        public registers_ (int sidelength_)// :this()
        {
            sidelength = sidelength_;
            dmatrixl = new double[sidelength,sidelength];
            dmatrixlw = new double[sidelength,sidelength];
            dmatrixin = new double[sidelength,sidelength];
            dvectorl = new double[sidelength];
            dvectorlw = new double[sidelength];
            dvectorin = new double[sidelength];
            dvectorv = null;
            dmatrixv = null;
            darray1 = null;
            darray2 = null;
            words1 = null;
            words2 = null;
            words3 = null;
            reset_arrays();
        }

        void reset_arrays()
        {
            for (int i = 0; i < sidelength; i++)
            {
                for (int j = 0; j < sidelength; j++)
                {
                    dmatrixl[i, j] = 0;
                    dmatrixlw[i, j] = 0;
                    dmatrixin[i, j] = 0;
                }
                dvectorl[i] = 0;
                dvectorlw[i] = 0;
                dvectorin[i] = 0;
            }            
        }

        public void reset_registers()
        {
            reset_arrays();
            dvarl = 0;
            dvarlw = 0;
            dvarres = 0;
            dfrom = 0;
            dto = 0;
        }

        public double [,] dmatrixl;
        public double [,] dmatrixlw;
        public double [,] dmatrixin;
        public double [] dvectorl;
        public double [] dvectorlw;
        public double [] dvectorin;
        public double dvarl = 0;
        public double dvarlw = 0;
        public double dvarres = 0;
        public double dfrom = 0;
        public double dto = 0;

        public double[,] dmatrixv;
        public double[] dvectorv;

        // freesize arrays : u can set its size freely by script
        // later will be implemented variable system
        public double[] darray1;
        public double[] darray2;

        // string pointers to process some data in extensions
        public string[] words1;
        public string[] words2;
        public string[] words3;

        public int ivar1 = 0;
        public int ivar2 = 0;

        //public int ivarl = 0;
        //public int ivarwl = 0;
        //public int ivarres = 0;

        public int sidelength;
    };*/

    public struct keep
    {
        public MemoryGates memg;
        public IConsole console;
//        public List<IExtension> xtensions;
    };

    class Interpreter
    {
        Interpreter( IConsole console_ )
        {
            flags = new flags_();
            expect = new expect_flags_();
            console = console_;

            memg = new MemoryGates();
//            extensions = new List<IExtension>();
            //REGISTER ALL THE EXTENSIONS HERE or somewhere else if ill make plugin system 
            
            updateDevice();

            flags.multilinemode = 0;
            flags.forceinputroute = 1;
            flags.forceautoinit = true;
            flags.input_type = 0;

            expect.nextlineinputmatrix = 0;
            expect.nextlineinputvector = 0;

            charSeparators = new char[] { ' ' };// legit lol
            console.Log("... Initialized\n");
            console.Log("... Ure Welcome :3\n");
        }

        // INTERFACE CONNECTION
        public void interpreteLine(ref string str_)
        {
            str = str_;
            string[] words = str.Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
            interpreteLine(ref words);
        }

        // interprete one line 
        void interpreteLine( ref string [] words )
        {
            if ( words[0] == "run" )
            {
                flags.multilinemode++;
//                string[] rows = System.IO.File.ReadAllLines(words[1]);
//                string[] tmparr;
                fileopened script = memg.openScriptFile(words[1]);
//                int from = 0;
                do
                {
                    memg.fio.getnextLine(ref script,true);
                    if ( script.words.Length != 0 )
                    {
                        interpreteLine(ref script.words);
                    }
                }
                while ( script.rows.Length != script.pointer );
                memg.closeScriptFile( script );

//                    tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
//                    while (tmparr.Length == 0)
//                    {
//                        from++;
//                        tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
//                    }

                    // input for extensions
                    //while ( expect.nextlineinputmatrix > 0 )
                    //{
                    //    if (flags.forceautoinit && ( tmparr.Length != reg.sidelength ))
                    //    {
                    //        reg = new registers_( tmparr.Length );
                    //        reg.reset_registers();
                    //        updateDevice();
                    //    }
                    //    // matrix input
                    //    dispatchMatrixInput( ref rows, ref from, ref tmparr )

                        
                    //    expect.nextlineinputmatrix--;
                    //}

                    //while ( expect.nextlineinputvector > 0 )
                    //{
                        
                    //}

                    //// if there is no inline input
                    //if ( ( expect.nextlineinputvector == 0 ) && ( expect.nextlineinputmatrix == 0 ) )
                    //{
                    //    if ( expect.extensionnum > 0 )
                    //    {
                    //        runExtension(expect.extensionnum);
                    //        expect.extensionnum = 0; // we just run it
                    //    }
                    //    interpreteLine(ref tmparr);
                    //}
                    //from++;
        //        }
        //        while (rows.Length != from);

                flags.multilinemode--;
            }
            if ( words[0] == "double" )
            {
//                gen_heap_elem tmp;
                if ( words[1] == "matrix" )
                {
                    if (words[2] == "name")
                    {
                        if(words[4] == "size")
                        {
                            memg.createDMatrixBySize(words[3],Convert.ToInt32(words[5]),Convert.ToInt32(words[6]));
                        }
                        else if ( words[4] == "from" )
                        {
                            memg.createDMatrixFromFile(words[3],words[5]);
                        }
                        else if ( words[4] == "copy" )
                        {
                            
                        }
//                        tmp.name += words[3];
                    }
                }
            }
/*            if (words[0] == "run")// first levl interpretation
            {
                flags.multilinemode++;
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

                    // input for extensions
                    while ( expect.nextlineinputmatrix > 0 )
                    {
                        if (flags.forceautoinit && ( tmparr.Length != reg.sidelength ))
                        {
                            reg = new registers_( tmparr.Length );
                            reg.reset_registers();
                            updateDevice();
                        }
                        // matrix input
                        dispatchMatrixInput( ref rows, ref from, ref tmparr )

                        
                        expect.nextlineinputmatrix--;
                    }

                    while ( expect.nextlineinputvector > 0 )
                    {
                        
                    }

                    // if there is no inline input
                    if ( ( expect.nextlineinputvector == 0 ) && ( expect.nextlineinputmatrix == 0 ) )
                    {
                        if ( expect.extensionnum > 0 )
                        {
                            runExtension(expect.extensionnum);
                            expect.extensionnum = 0; // we just run it
                        }
                        interpreteLine(ref tmparr);
                    }
                    from++;
                }
                while (rows.Length != from);

                flags.multilinemode--;
            }*/
/*            else if (words[0] == "init")
            {
                if (words[1] == "auto")
                {
                    if ( words[2] == "true" )
                        {flags.forceautoinit = true;}
                    else if ( words[2] == "false" )
                        {flags.forceautoinit = false;}
                }
                else if (words[1] == "length")
                {
                    if ( !flags.forceautoinit )
                    {
                        reg = new registers_( Convert.ToInt32(words[2]) );
                        updateDevice();
                    }
                }
            }*/
            else if (words[0] == "execute")
            {
                if (words[1] == "extension")
                {
                    int extnum = Convert.ToInt32(words[2]);
                    //for (int i = 2; i < words.Count(); i++)
                    int i = 3;
                    int counter = 0;

                    List<ExtensionParam> parnamed = memg.getExtension(extnum).ParamNamed;
                    List<ExtensionParam> parstrict = memg.getExtension(extnum).ParamStrict;

//                    Extensions.ExtensionParam par = device.xtensions[extnum].ParamStrict[counter];
                    // searchname
//                    bool strictparampassed = false;
//                    string name_;
//                    core.E_HEAP_TYPE type_;

                    bool paramfound = true;
                    ExtensionParam par = new ExtensionParam();

                    while ( i < words.Length )
                    {
                        if ( counter < parstrict.Count )
                        {   
                            par = parstrict[counter];
                            counter++;
                        }
                        else
                        {
                            paramfound = false;
                            for (int k = 0; k < parnamed.Count; k++)
                            {
                                if (words[i] == parnamed[k].name)
                                {
                                    par = parnamed[k];
                                    paramfound = true;
                                    i++;
                                }
                            }
                        }

                        // finalizing : adding parameter
                        if (paramfound)// throw exceptions?
                        {
                            switch (par.type)//maybe u should throw xeptions here lel
                            {
                                case core.E_HEAP_TYPE.STRING:
                                    {
                                        string pass = null;
                                        int beginword = -1, endword = -1;
                                        beginword = i;
                                        int pointer = 1;
                                        if (words[i][0] == '\"' || words[i][0] == '\'')
                                        {
                                            while (i < words.Count())
                                            {
                                                if (pointer == words[i].Length)//"swag", " swag ", "swag ", swag, '' " swag "
                                                {
                                                    if (i == beginword)
                                                    {
                                                        pass = String.Copy(words[i]).Remove(0, 1);
                                                    }
                                                    else
                                                    {
                                                        if (pass.Length != 0)
                                                            { pass += ' ' + words[i]; }
                                                        else
                                                            { pass = String.Copy(words[i]); }
                                                    }
                                                    i++;
                                                    pointer = 0;
                                                }

                                                if (words[i][pointer] == '\"')
                                                {
                                                    endword = i;
                                                    if (pointer != words[i].Length - 1)
                                                    {
                                                        // ERROR "adssa"asd space is missing
                                                    }
                                                    else
                                                    {
                                                        if (i == beginword)
                                                        { 
                                                            pass = String.Copy(words[i]).Remove(words[i].Length - 1);
                                                            pass = pass.Remove(pass.Length - 1);
                                                        }
                                                        else
                                                        {
                                                            if (pass.Length == 0)
                                                            {
                                                                pass = String.Copy(words[i]).Remove(words[i].Length - 1);
                                                            }
                                                            else 
                                                            {
                                                                if (words[i].Length > 1)
                                                                {
                                                                    pass += ' ' + String.Copy(words[i]).Remove(words[i].Length - 1);
                                                                }
                                                            }
                                                        }
 //                                                       else
 //                                                       { pass += String.Copy(words[i]).Remove(words[i].Length - 1); }// += with LAST removed

                                                        if (i == beginword)
                                                        {
                                                            pass = pass.Remove(pass.Length - 1); // remove FIRST if its a first word
                                                        }
                                                    }
                                                    break;
                                                }
                                                else
                                                {
                                                  //  pass += words[i][pointer];
                                                    pointer++;
                                                }
                                            }
//                                            if (i == beginword)
//                                                { pass = String.Copy(words[i]).Remove(0, 1); }

                                        }
/*                                      //if (words[i][0] == '"')
                                        //{
                                        //    int pointer = 1;
                                        //    int begin = i;
                                        //    int end = -1;
                                            
                                        //    string tmp = String.Copy( pass );
                                        //    //int i = 0;
                                        //    //"bla "
                                        //    while ( i < words.Count() )
                                        //    {
                                        //        if (pointer == words[i].Length)//"swag", " swag ", "swag ", swag, '' 
                                        //        {
                                        //            i++;
                                        //            pointer = 0;
                                        //        }

                                        //        if (words[i][pointer] == '"')
                                        //        {
                                        //            end = i;
                                        //            break;
                                        //        }
                                        //        else
                                        //        {
                                        //            pass += words[i][pointer];
                                        //            pointer++;
                                        //        }
                                        //    }

                                        //    if (end == -1)
                                        //    {
                                        //        // error
                                        //    }
                                        //}*/
                                        device.memg.createParamString(ref pass, ref par);
                                    }
                                    break;
                                case core.E_HEAP_TYPE.INTEGER:
                                    {
                                        int pass = Convert.ToInt32(words[i]);
                                        device.memg.createParamInteger(ref pass, ref par);
                                    }
                                    break;
                                case core.E_HEAP_TYPE.DOUBLE:
                                    {
                                        double pass = Convert.ToDouble(words[i]);
                                        device.memg.createParamDouble(ref pass, ref par);
                                    }
                                    break;
                                case core.E_HEAP_TYPE.DOUBLE_ARRAY:
                                    { }
                                    break;
                                case core.E_HEAP_TYPE.DOUBLE_MATRIX:
                                    { }
                                    break;
                            };
                        }
                        i++;
                    }

                    // handle parameters
                    //counter++;
                    //if ( words.Count() - i > 0 )
                    //{
                    //    while (i < words.Count())
                    //    {
                    //        if ( par. )
                    //        {
                    //        }
                    //        gen_heap_elem tmp = new 
                    //        device.memg.reg.ExtensionParamList.Add();
                    //    }
                    //}
                }
            }
/*            else if ( words[0] == "setparam" )
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
                                setRegisterIntParam(E_REGISTER_TYPE.DARRAYFS, id, Convert.ToInt32(words[6]));
                            }
                        }
                    }
                }
                else if (words[1] == "int")
                {

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
            }*/
        }



//        void inputFromFileDMatrixLR ( ref string filename )
//        {
//            inputFromFileDMatrix(ref filename, ref reg.dmatrixl);
        //}
        //void inputFromFileDMatrixIN ( ref string filename )
        //{
        //    inputFromFileDMatrix(ref filename, ref reg.dmatrixin);
        //}

        //enum E_REGISTER_TYPE
        //{
        //    DARRAYFS,
        //    NUMBER
        //};

        // DANGEROUS :: all parts, where these arrays are used must be updated, so arrays will be garbage collected
 /*       void setRegisterIntParam( E_REGISTER_TYPE type, int id, int val = 0, int param = 0 )// param if required
        {
            switch (type)
            { 
                case E_REGISTER_TYPE.DARRAYFS:
                {
                    if ( id == 1 )
                    {
                        reg.darray1 = null;
                        reg.darray1 = new double[val];
                    }
                    else if (id == 2)
                    {
                        reg.darray2 = null;
                        reg.darray2 = new double[val];
                    }
                }
                break;
                default:
                {}
                break;
            }
        }*/

        void runExtension( int num )
        {
/*            if (num == 1)
            {
                // eigenvalue extension run()
                // TODO:: implement OOP approach to extensions
                eigenvalue egv = new eigenvalue();
                egv.eigenProc(ref reg);

                for (int i = 0; i < reg.x.Count; i++)
                {
                    console.consoleWindow.AppendText(reg.x[i].ToString() + " " + reg.y[i].ToString() + "\n");
                }
            }*/
        }

/*        void dispatchMatrixInput( ref string [] rows_, ref int from_, ref string [] tmparr_ )
        {
            switch ( flags.forceinputroute )
            {
                case 1:
                    {inputFromTextChunkDMatrix(ref rows_, ref from_, ref reg.dmatrixl, ref tmparr_);}
                break;
                case 2:
                break;
                default:
                    { inputFromTextChunkDMatrix(ref rows_, ref from_, ref reg.dmatrixin, ref tmparr_); }
                break;
            }
        }*/

        

        void updateDevice()
        {
            device.memg = memg;
//            device.stk = stk;
            device.console = console;
//            device.xtensions = extensions;
        }
        
        
        char[] charSeparators;

        // internal buffers
        string str;

        // states
        private struct flags_
        {
            public bool forceautoinit;
            public int forceinputroute;// 0 in; 1 l; 2 r;
            public int multilinemode;// level
            public int input_type;// 0 str; 1 int; 2 double;
        };
        private struct expect_flags_
        {
            public int nextlineinputmatrix;
            public int nextlineinputvector;
            public int extensionnum;
        };

        // various registers for script machine
        private flags_ flags;
        private expect_flags_ expect;

        // device aliases for quicker access :3
        private MemoryGates memg;

        IConsole console;

//        List<IExtension> extensions;

        private keep device;
    }
}

