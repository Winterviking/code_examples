using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5th
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            register reg = new register();
            string str = textBox1.Text;

            scriptInterpreter inter = new scriptInterpreter();
            Console console = new Console();
            console.consoleWindow = richTextBox1;
            inter.Initialize(console);
            inter.interpreteLine(ref str);
//            str = System.Text.RegularExpressions.Regex.Replace(str, " +", " ");
//            str.Trim();
 ///           char[] charSeparators = new char[] {' '};
//            string[] words = str.Split( charSeparators, StringSplitOptions.RemoveEmptyEntries);
            
/*            if ( words[0] == "run" )
            {
                string[] rows = System.IO.File.ReadAllLines(words[1]);
                string[] tmparr;
                int from = -1;
                
                do
                {
                    from++;
                    tmparr = rows[from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                    richTextBox1.AppendText(tmparr.Length.ToString() + ' ');
                }
                while (tmparr.Length == 0);

                reg.sidelength = tmparr.Length;
                reg.init_registers();
//                reg.dmatrix = new double[reg.sidelength, reg.sidelength];

                for (int i = 0; i < reg.sidelength; i++)
                {
                    tmparr = rows[i + from].Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                    for (int j = 0; j < reg.sidelength; j++)
                    {
                        reg.ldmatrix[i, j] = Convert.ToDouble(tmparr[j], System.Globalization.CultureInfo.InvariantCulture);
                        richTextBox1.AppendText(reg.ldmatrix[i, j].ToString() + ' ');
                    }
                    richTextBox1.AppendText("\n");
                }
            }
 * */
        }
    }
}
