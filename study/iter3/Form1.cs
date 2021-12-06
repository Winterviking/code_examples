using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5th_just_prog
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            core cr = new core( richTextBox1 );
            cr.Run();
//            cr.initSysIO(richTextBox1);
//            ServiceMath mth = new ServiceMath();
//            double [,] mat = cr.MatrixInput(cr.sysio.OpenFile("matrix.txt"));
//            ServiceMath sm = new ServiceMath();
//            sm.mm = cr.mm;
//            double lol = ServiceMath.determinant(mat, cr.mm.sidelength);

//            cr.sysio.Log( sm.MaxLambda(mat).ToString() );

//            cr.matrixOutput( mat );
//            cr.sysio.Log(lol.ToString());
            
        }
    }
}
