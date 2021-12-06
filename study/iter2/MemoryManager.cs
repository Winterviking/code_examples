using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th2nd
{
    namespace core
    {
        public enum E_HEAP_TYPE
        {
            INTEGER,
            DOUBLE,
            INTEGER_ARRAY,
            DOUBLE_ARRAY,
            INTEGER_MATRIX,
            DOUBLE_MATRIX,
            STRING,
            STRING_ARRAY
        }


        public class gen_heap_elem
        {
            public int id;
            public E_HEAP_TYPE type;
            public string name;
            public bool system;
        }

        public struct array
        {
            public Array arraydata;
            public int[] sidelength;

            public int x
            {
                get { return sidelength[0]; }
                set { sidelength[0] = value; }
            }
            public int y
            {
                get { return sidelength[1]; }
                set { sidelength[1] = value; }
            }
            public int z
            {
                get { return sidelength[2]; }
                set { sidelength[2] = value; }
            }
        }

        // MIGHTY keeper of references :3
        public class MemoryManager
        {
            public MemoryManager()
            {
                // real memory
                int_pool = new List<int?>();
                double_pool = new List<double?>();
                array_pool = new List<array?>();
                

                // index
                free_memory_int = new List<gen_heap_elem>();
                free_memory_double = new List<gen_heap_elem>();
                free_memory_array_int = new List<gen_heap_elem>();
                free_memory_array_double = new List<gen_heap_elem>();
                free_memory_matrix_int = new List<gen_heap_elem>();
                free_memory_matrix_double = new List<gen_heap_elem>();
            }

            public void reset()
            {
                int_pool.Clear();
                double_pool.Clear();
                array_pool.Clear();
                string_pool.Clear();

                free_memory_int.Clear();
                free_memory_double.Clear();
                free_memory_array_int.Clear();
                free_memory_array_double.Clear();
                free_memory_matrix_int.Clear();
                free_memory_matrix_double.Clear();
                free_memory_string.Clear();
                free_memory_array_string.Clear();
            }

            // variables
            List<int?> int_pool;
            List<double?> double_pool;
            // array variables
            List<array?> array_pool;

            // string 
            List<string> string_pool;

            // index
            List<gen_heap_elem> free_memory_int;
            List<gen_heap_elem> free_memory_double;
            List<gen_heap_elem> free_memory_array_int;
            List<gen_heap_elem> free_memory_array_double;
            List<gen_heap_elem> free_memory_matrix_int;
            List<gen_heap_elem> free_memory_matrix_double;
            List<gen_heap_elem> free_memory_string;
            List<gen_heap_elem> free_memory_array_string;

            // SET VARIABLE BLOCK
            public gen_heap_elem create_int_variable(ref int par, bool system = false)
            {
                gen_heap_elem tmp;
                if (free_memory_int.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = int_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER;
                    int_pool.Add(par);
                }
                else
                {
                    tmp = free_memory_int[0];
                    free_memory_int.RemoveAt(0);
                    int_pool[tmp.id] = par;
                }

                tmp.system = system; 
                return tmp;
            }

            public gen_heap_elem create_double_variable(ref double par, bool system = false)
            {
                gen_heap_elem tmp;
                if (free_memory_double.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = double_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER;
                    double_pool.Add(par);
                }
                else
                {
                    tmp = free_memory_double[0];
                    free_memory_double.RemoveAt(0);
                    double_pool[tmp.id] = par;
                }
                tmp.system = system;
                return tmp;
            }

            public gen_heap_elem create_string_variable(ref string par, bool system = false)
            {
                gen_heap_elem tmp;
                if (free_memory_string.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = int_pool.Count;
                    tmp.type = E_HEAP_TYPE.STRING;
                    string_pool.Add(par);

                }
                else
                {
                    tmp = free_memory_string[0];
                    free_memory_string.RemoveAt(0);
                    string_pool[tmp.id] = par;
                }

                tmp.system = system; 
                return tmp;
            }

            // maby change to * coz 500 issues
            public gen_heap_elem create_int_array(ref int[] par, bool system = false)
            {
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[1];
                newcomer.x = par.Length;

                if (free_memory_array_int.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER_ARRAY;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_array_int[0];
                    free_memory_array_int.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;
            }

            public gen_heap_elem create_double_array(ref double[] par, bool system = false)
            {
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[1];
                newcomer.x = par.Length;

                if (free_memory_array_double.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.DOUBLE_ARRAY;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_array_double[0];
                    free_memory_array_double.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;
            }

            public gen_heap_elem create_string_array(ref string[] par, bool system = false)
            {
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[1];
                newcomer.x = par.Length;

                if (free_memory_array_string.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.STRING_ARRAY;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_array_string[0];
                    free_memory_array_int.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;
            }


            public gen_heap_elem create_int_matrix(ref int[,] par, int x, int y = 0, bool system = false)
            {
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[2];
                newcomer.x = x;
                if ((y == 0))
                    { newcomer.y = x; }
                else
                    { newcomer.y = y; }

                if (free_memory_matrix_int.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER_MATRIX;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_matrix_int[0];
                    free_memory_matrix_int.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;
            }

            public gen_heap_elem create_double_matrix(ref double[,] par, int x, int y = 0, bool system = false)
            {
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[2];
                newcomer.x = x;
                if ((y == 0))
                    { newcomer.y = x; }
                else
                    { newcomer.y = y; }

                if (free_memory_matrix_double.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER_MATRIX;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_matrix_double[0];
                    free_memory_matrix_double.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;
            }

            public gen_heap_elem createDoubleMatrix(string name, double [,] par = null, int x = 0, int y = 0, bool system = false, bool locked = false)
            {
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[2];
                newcomer.x = x;
                if ((y == 0))
                { newcomer.y = x; }
                else
                { newcomer.y = y; }

                if (free_memory_matrix_double.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER_MATRIX;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_matrix_double[0];
                    free_memory_matrix_double.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;
            }

            public gen_heap_elem create_named_stab( E_HEAP_TYPE type, string name )
            {
                gen_heap_elem tmp = new gen_heap_elem();
                switch (type)
                {
                    case E_HEAP_TYPE.DOUBLE:
                        {
                            array arr = new array();
                            arr.x = 0;
                            arr.y = 0;
                            array_pool.Add(arr);
                        }
                        break;
                    case E_HEAP_TYPE.INTEGER:
                        { 
                        
                        }
                        break;
                    case E_HEAP_TYPE.DOUBLE_MATRIX:
                        { 
                            
                        }
                        break;
                }

                /*
                gen_heap_elem tmp;
                array newcomer = new array();
                newcomer.arraydata = par;
                newcomer.sidelength = new int[2];
                newcomer.x = x;
                if ((y == 0))
                    { newcomer.y = x; }
                else
                    { newcomer.y = y; }

                if (free_memory_matrix_double.Count == 0)
                {
                    tmp = new gen_heap_elem();
                    tmp.id = array_pool.Count;
                    tmp.type = E_HEAP_TYPE.INTEGER_MATRIX;
                    array_pool.Add(newcomer);
                }
                else
                {
                    tmp = free_memory_matrix_double[0];
                    free_memory_matrix_double.RemoveAt(0);
                    array_pool[tmp.id] = newcomer;
                }

                tmp.system = system;
                return tmp;                 
                 */
            }

            public int retrieveIntParameter(gen_heap_elem to_find)
            {
                return int_pool[to_find.id].Value;
            }

            public double retrieveDoubleVariable(gen_heap_elem to_find)
            {
                return double_pool[to_find.id].Value;
            }

            public string retrieveStringVariable(gen_heap_elem to_find)
            {
                return string_pool[to_find.id];
            }

            public array retrieveArrayVariable(gen_heap_elem to_find)
            {
                return array_pool[to_find.id].Value;
            }

            //public int teeest()
            //{
            //    return free_memory_int.Count;
            //}

            // With possibility to drop internal reference for GC
            public bool remove_variable(gen_heap_elem to_delete, bool force_ref_drop = false)
            {
                to_delete.system = false;
                bool success = false;
                switch (to_delete.type)
                {
                    case E_HEAP_TYPE.INTEGER:
                        {
                            //int_pool.RemoveAt(to_delete.id);
                            if (force_ref_drop)
                            { int_pool[to_delete.id] = null; }
                            else
                            { int_pool[to_delete.id] = 0; }

                            free_memory_int.Add(to_delete);
                            success = true;
                        }
                        break;
                    case E_HEAP_TYPE.DOUBLE:
                        {
                            //double_pool.RemoveAt(to_delete.id);
                            if (force_ref_drop)
                            { double_pool[to_delete.id] = null; }
                            else
                            { double_pool[to_delete.id] = 0; }
                            free_memory_double.Add(to_delete);
                            success = true;
                        }
                        break;
                    case E_HEAP_TYPE.INTEGER_ARRAY:
                        {
                            //                        array_pool.RemoveAt(to_delete.id);
                            if (force_ref_drop)
                            { array_pool[to_delete.id] = null; }
                            else
                            { Array.Clear(array_pool[to_delete.id].Value.arraydata, array_pool[to_delete.id].Value.arraydata.GetLowerBound(0), array_pool[to_delete.id].Value.arraydata.GetUpperBound(0)); }
                            free_memory_array_int.Add(to_delete);
                            success = true;
                        }
                        break;
                    case E_HEAP_TYPE.DOUBLE_ARRAY:
                        {
                            if (force_ref_drop)
                            { array_pool[to_delete.id] = null; }
                            else
                            { Array.Clear(array_pool[to_delete.id].Value.arraydata, array_pool[to_delete.id].Value.arraydata.GetLowerBound(0), array_pool[to_delete.id].Value.arraydata.GetUpperBound(0)); }
                            free_memory_array_double.Add(to_delete);
                            success = true;
                        }
                        break;
                    case E_HEAP_TYPE.STRING:
                        {
                            if (force_ref_drop)
                            { string_pool[to_delete.id] = null; }
                            else
                            { string_pool[to_delete.id] = ""; }
                            free_memory_string.Add(to_delete);
                            success = true;
                        }
                        break;
                    case E_HEAP_TYPE.STRING_ARRAY:
                        {
                            if (force_ref_drop)
                            { array_pool[to_delete.id] = null; }
                            else
                            { Array.Clear(array_pool[to_delete.id].Value.arraydata, array_pool[to_delete.id].Value.arraydata.GetLowerBound(0), array_pool[to_delete.id].Value.arraydata.GetUpperBound(0)); }
                            free_memory_array_string.Add(to_delete);
                            success = true;
                        }
                        break;
                }
                return success;
            }
        }
    }
}
