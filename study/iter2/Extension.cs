using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th2nd
{
    namespace Extensions
    {
        //enum E_EXT_PARAM
        //{ 
        //    STRING,
        //    INTEGER,
        //    DOUBLE,
        //    DMATRIX,
        //    DVECTOR,
        //    NUMBER
        //}

        public struct ExtensionParam
        {
//            public E_EXT_PARAM type;
            public core.E_HEAP_TYPE type;
            public string name;
            public int id;
            public core.gen_heap_elem var;
            public bool locked;
        }

        struct Alias
        {
            string name;
            string alias;
            string[] format;
        }


        //struct ExtensionParam
        //{
        //    public int matrices = 0;
        //    public int vectors = 0;
        //    public int strings = 0;
        //    public int doubles = 0;
        //    public int integers = 0;
        //    public string[] smatrices = null;
        //    public string[] svectors = null;
        //    public string[] sstrings = null;
        //    public string[] sdoubles = null;
        //    public string[] sintegers = null;
        //}

        public interface IExtension
        {
            void execute();

            keep Device
            {
                get;
                set;
            }

            List<ExtensionParam> ParamNamed
            {
                get;
                set;
            }

            List<ExtensionParam> ParamStrict
            {
                get;
                set;
            }

            int ID
            {
                get;
                set;
            }
            //public ExtensionParam Param
            //{
            //    get;
            //}
        }

        public abstract class Extension : IExtension
        {
            protected Extension()
            {
                paramnamed = new List<ExtensionParam>();
                paramstrict = new List<ExtensionParam>();
                paramid = 0;
                id_lock = false;
//                param = new ExtensionParam();
//                extparam = new ext_param
            }

            public abstract void execute();

            public keep Device
            {
                get { return device; }
                set { device = value; }
            }
            public List<ExtensionParam> ParamNamed
            {
                get { return paramnamed; }
                set { paramnamed = value; }
            }
            public List<ExtensionParam> ParamStrict
            {
                get { return paramstrict; }
                set { paramstrict = value; }
            }
            public int ID
            {
                get { return id; }
                set 
                {
                    if (!id_lock)
                    {
                        id = value;
                        id_lock = true;
                    }
                }
            }

//            abstract public void execute();
            //public ExtensionParam Param
            //{
            //    get { return param; }
            //}

            protected List<ExtensionParam> paramnamed;
            protected List<ExtensionParam> paramstrict;
            protected keep device;
            protected int paramid;
            protected int id;
            private bool id_lock;

            protected ExtensionParam addParam(core.E_HEAP_TYPE type, string name = null, bool strict = false, bool locked = false)
            {
                ExtensionParam tmp = new ExtensionParam();
                tmp.type = type;
                tmp.name = name;
                paramid++;
                tmp.id = paramid;
                tmp.locked = locked;

                if ( strict ) 
                {
                    paramstrict.Add(tmp);
                }
                else
                {
                    paramnamed.Add(tmp);
                }
                return tmp;
            }
//            protected ext_param extparam;
        }

        public abstract class IOExtension : Extension
        {
            public IOExtension()
            {
                // first param is allways "input" or "output" string
                // execute extension 1 input
                addParam(core.E_HEAP_TYPE.STRING, "/ioparam", true, true);
            }
            public override void execute()
            {
                if (paramstrict[0].type == core.E_HEAP_TYPE.STRING)
                {
                    string param = device.memg.mm.retrieveStringVariable(paramstrict[0].var);// TODO
                    if ( param == "input")
                    {
                        Input();
                    }
                    else if ( param == "output" )
                    {
                        Output();
                    }
                }
            }
            protected abstract void Input();
            protected abstract void Output();
        }


        //class MatrixOutput : Extension
        //{
        //    public MatrixOutput(keep data_)
        //    {
        //        device = data_;
        //        //param.integers = 1;
        //        //param.sintegers = new string[] { "one" };
        //    }

        //    void execute()
        //    {
        //        double[,] mat = device.memg.reg.dmatrixv;
        //        if (mat != null)
        //        {
        //            for (int i = 0; i < device.reg.sidelength; i++)
        //            {
        //                for (int j = 0; j < device.reg.sidelength; j++)
        //                {
        //                    device.console.Log(mat[i, j].ToString() + ' ');
        //                }
        //                device.console.Log("\n");
        //            }
        //        }
        //        else
        //        {
        //            device.console.Log("Error\n");
        //        }
        //    }
        //}

        //class MatrixInput : Extension
        //{
        //    public MatrixInput(keep data_)
        //    {
        //        device = data_;
        //        //           param.integers = 1;
        //        param.sstrings = new string[] { "filename" };
        //    }

        //    void execute()
        //    {

        //    }

        //    void test(ref string[] words, int depth)
        //    {

        //    }
        //}
    }
}
