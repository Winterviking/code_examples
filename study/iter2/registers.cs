using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th2nd
{
    namespace core
    {
        public class registers
        {
            public registers()
            {
                dlistinx = new List<double>();
                dlistiny = new List<double>();
                dlistinz = new List<double>();

                dlistoutx = new List<double>();
                dlistouty = new List<double>();
                dlistoutz = new List<double>(); 
            }
            // settings
            public int sidelength;

            //VIRTUAL REGISTERS
            // generic
            public double[,] vdmatrixl = null;
            public double[,] vdmatrixlw = null;

            public double[] vdvectorl = null;
            public double[] vdvectorlw = null;

            public double? dvarl = null;
            public double? dvarlw = null;
            public double? dvarres = null;

            // input
            public double[,] vdmatrixin = null;
            public double[] vdvectorin = null;
            public double? dvarin = null;

            // output
            public double[,] vdmatrixout = null;
            public double[] vdvectorout = null;
            public double? dvarout = null;

            // interval register
            public double? dfrom = null;
            public double? dto = null;

            //REAL REGISTERS ( if needed in future )
            // dump lists for outputs :3
            // TODO::: maby pair or vector class is better to use here
            public List<double> dlistinx;
            public List<double> dlistiny;
            public List<double> dlistinz;

            public List<double> dlistoutx;
            public List<double> dlistouty;
            public List<double> dlistoutz;

            //RESET REGISTERS
            public void resetGeneric()
            {
                vdmatrixl = null;
                vdmatrixlw = null;

                vdvectorl = null;
                vdvectorlw = null;

                dvarl = null;
                dvarlw = null;
                dvarres = null;
            }
            public void resetInput()
            {
                vdmatrixin = null;
                vdvectorin = null;
                dvarin = null;
            }
            public void resetOutput()
            {
                vdmatrixout = null;
                vdvectorout = null;
                dvarout = null;
            }
            public void resetInterval()
            {
                dfrom = null;
                dto = null;
            }
            public void resetAllRegisters()
            {
                resetGeneric();
                resetInput();
                resetOutput();
                resetInterval();
            }

            public void resetIOLists()
            { 
                dlistinx.Clear();
                dlistiny.Clear();
                dlistinz.Clear();

                dlistoutx.Clear();
                dlistouty.Clear();
                dlistoutz.Clear();            
            }
//            public void resetExtensionParamList()
//            {
//                ExtensionParamList.Clear();
//            }
            public void resetScopeVariableList()
            {
                ScopeVariableList.Clear();
            }

            public void resetAllLists()
            {
                resetIOLists();
//                resetExtensionParamList();
                resetScopeVariableList();
            }

            //PARAMETERS REGISTERS
//            public List<gen_heap_elem> ExtensionParamList = new List<gen_heap_elem>();
            public List<gen_heap_elem> ScopeVariableList = new List<gen_heap_elem>();// maby make list of those lol if script machine will become badass one day lol
            public List<fileopened> ScriptTree = new List<fileopened>();

        }
    }
}
