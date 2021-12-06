using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _5th2nd.Extensions;

namespace _5th2nd
{
    namespace core
    {
        public class MemoryGates
        {
            public registers reg = new registers();
            public MemoryManager mm = new MemoryManager();
            public FileIO fio = new FileIO();
            public ExtensionFactory efc = new ExtensionFactory();

            public void resetMemoryGate()
            {
                // reset registers
                reg.resetAllRegisters();
                reg.resetAllLists();
                reg.sidelength = -1;

                // reset MemoryManager
                mm.reset();
            }

            public IExtension getExtension ( int id )
            {
                return efc.getExtensionRefByNumber( id );
            }

            public fileopened openScriptFile( string filename )
            {
                fileopened bc = fio.OpenFile(filename);
                reg.ScriptTree.Add(bc);
                return bc;
            }

            public void closeScriptFile( fileopened file )
            {
                reg.ScriptTree.Remove(file);
            }

            public void configMemoryGate(int length)
            {
                reg.sidelength = length;
            }

            public gen_heap_elem createDMatrixFromFile(string name, string filename)
            { return createDoubleMatrix(name, 0, 0, filename); }
            public gen_heap_elem createDMatrixBySize(string name, int x, int y)
            { return createDoubleMatrix(name,x,y); }
            public gen_heap_elem createDMatrix(string name, fileopened xistinnfile)
            { return createDoubleMatrix(name, 0, 0, null, xistinnfile); }

            public gen_heap_elem createDoubleMatrixNamed(string name)
            { 
                
            }


            public gen_heap_elem createDoubleMatrix(string name, int x = 0, int y = 0 , string filename = null, fileopened? xistinnfile = null, string copytoname = null )
            {
                double [,] mat = null;
                gen_heap_elem tmp;
                if ( x != 0 )
                {
                    if ( y == 0 )
                        { y = x; }
                    mat = new double [x,y];
                    tmp = mm.create_double_matrix(ref mat,x,y );
                }
                else if ( filename != null )
                {
                    mat = getMatrixFromFile(fio.OpenFile(filename), ref x, ref y);
                    tmp = mm.create_double_matrix(ref mat, x,y);
                }
                else if ( xistinnfile != null )
                {
                    mat = getMatrixFromFile(xistinnfile.Value, ref x, ref y);
                    tmp = mm.create_double_matrix(ref mat, x,y);
                }
                //else if ( copytoname != null )
                //{
                //}
                else
                {
                    mat = new double[reg.sidelength, reg.sidelength];
                    tmp = mm.create_double_matrix(ref mat, reg.sidelength);
                }
                tmp.name = name;

                reg.ScopeVariableList.Add(tmp);
                
                return tmp;
            }

            double [,] getMatrixFromFile( fileopened file, ref int x, ref int y )
            {
                int from,to;

                List<string[]> chunk = new List<string[]>();
                do
                    fio.getnextLine( ref file, true );
                while ( file.words.Length == 0 );

                x = file.words.Length;
                from = file.pointer;
                chunk.Add(file.words);
                
                do
                {
                    fio.getnextLine( ref file, true );
                    chunk.Add(file.words);
                }
                while ( ( ( file.pointer + 1 ) != file.rows.Length ) && ( file.words.Length == x ) );

                if ( ( file.words.Length == x ) )
                    {to = file.pointer;}
                else
                    {to = file.pointer--;}
                y = to - from;
                y++;

                return getMatrixFromTextChunk(chunk,x,y);
            }

            double [,] getMatrixFromTextChunk ( List<string[]> chunk, int x, int y )
            {
                double [,] mat = new double [x,y];

                for (int i = 0; i < x; i++)
			    {
                    for (int j = 0; j < y; j++)
			            { mat[i,j] = Convert.ToDouble( chunk[i][j] ); }
			    }
                return mat;
            }

            public gen_heap_elem createParamString(ref string param, ref ExtensionParam par)
            {
                gen_heap_elem tmp = mm.create_string_variable(ref param, true);
                tmp.name = par.name;

                par.var = tmp;
//                reg.ExtensionParamList.Add(tmp);
                return tmp;
            }
            public gen_heap_elem createParamDouble(ref double param, ref ExtensionParam par, string name = null)
            {
                gen_heap_elem tmp = mm.create_double_variable(ref param, true);
                tmp.name = par.name;

                par.var = tmp;
//                reg.ExtensionParamList.Add(tmp);
                return tmp;
            }
            public gen_heap_elem createParamInteger(ref int param, ref ExtensionParam par, string name = null)
            {
                gen_heap_elem tmp = mm.create_int_variable(ref param, true);
                tmp.name = par.name;

                par.var = tmp;
//                reg.ExtensionParamList.Add(tmp);
                return tmp;
            }

            public void clearExtensionParams( int id )
            {
                // Clear All The Params
                IExtension iext = getExtension( id );

                for (int i = 0; i < iext.ParamStrict.Count; i++)
                {
                    if ( iext.ParamStrict[i].var != null )
                    {
                        mm.remove_variable(iext.ParamStrict[i].var);
                    }
                }

                for (int i = 0; i < iext.ParamNamed.Count; i++)
                {
                    if (iext.ParamStrict[i].var != null)
                    {
                        mm.remove_variable(iext.ParamNamed[i].var);
                    }
                }
            }

            //void inputFromTextChunkDMatrix(, ref double[,] where, ref string[] firstline)
            //{
            //    string[] tmparr;

            //    for (int i = 0; i < reg.sidelength; i++)
            //    {
            //        if (i == 0)
            //        { tmparr = firstline; }
            //        else
            //        { tmparr = rows_[i + from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries); }
            //        for (int j = 0; j < reg.sidelength; j++)
            //        {
            //            where[i, j] = Convert.ToDouble(tmparr[j], System.Globalization.CultureInfo.InvariantCulture);
            //            console.Log(where[i, j].ToString() + ' ');
            //        }
            //        console.Log("\n");
            //    }
            //    from += reg.sidelength - 1;
            //}

            //void inputFromFileDMatrix(ref string filename, ref double[,] where)
            //{
            //    do
            //    {
            //        from++;
            //        tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
            //        console.consoleWindow.AppendText(tmparr.Length.ToString() + ' ');
            //    }
            //    while (tmparr.Length == 0);

            //    if ((tmparr.Length != reg.sidelength) && flags.forceautoinit)
            //    {
            //        reg = new registers_(tmparr.Length);
            //        updateDevice();
            //    }

            //    inputFromTextChunkDMatrix(ref rows, ref from, ref where, ref tmparr);
            //}
        }
    }
}
