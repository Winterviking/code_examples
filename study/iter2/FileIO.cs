using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th2nd
{
    namespace core
    {
        public struct fileopened
        {
            public string[] rows;
            public string[] words;
            public string row;
            public int pointer;
        }

        public class FileIO
        {
            public void getnextLine( ref fileopened file, bool words = false )
            {
                file.pointer++;
                file.row = file.rows[file.pointer];
                if ( words )
                {
                    file.words = file.row.Split(charSeparators, StringSplitOptions.RemoveEmptyEntries);
                }
            }

            public fileopened OpenFile( string filename )
            {
                fileopened file = new fileopened();
                
                file.rows = System.IO.File.ReadAllLines(filename);
                file.pointer = -1;
                files.Add(file);

                return file;
            }

            public void CloseFile( fileopened file )
            {
                files.Remove(file);
            }
            
            List<fileopened> files;
            char[] charSeparators = { ' ' };
        }
    }
}
