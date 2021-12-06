using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _5th2nd.Extensions.Internal;

namespace _5th2nd
{
    namespace Extensions
    {
        public class ExtensionFactory // TODO:: can be refactored into interface easilly
        {
            public ExtensionFactory()
            {
                // MATRIX IO Internal Extension
                matrixio = new MatrixIO();
                matrixio.ID = pool.Count + 1;
                pool.Add(matrixio);
                //
            }
            public IExtension getExtensionRefByNumber( int id )
            {
                return pool.ElementAt(id);
            }

            // getters for extensions
            public MatrixIO getMatrixIOExtension()
            {
                return matrixio;
            }

            // Extension references
            MatrixIO matrixio;

            // storage variables
            List<IExtension> pool;
        }
    }
}
