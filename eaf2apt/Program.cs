using System;
using System.Globalization;
namespace eaf2apt
{
    class Program
    {
        static void Main(string[] args)
        {
            CultureInfo.CurrentCulture = CultureInfo.InvariantCulture;
            if (args.Length == 0)
            {
                Console.WriteLine();
                Console.WriteLine("Usage: eaf2apt infile --ra3 --optimize");
                Console.WriteLine();
                Console.WriteLine("infile is the name of the input file");
                Console.WriteLine("pass --ra3 if you are exporting for RA3 rather than C&C3");
                Console.WriteLine("pass --optimize if you want to optimize the input file");
                Console.WriteLine();
            }
            bool optimize = false;
            bool isra3 = false;
            foreach (var arg in args)
            {
                if (arg == "--ra3")
                {
                    isra3 = true;
                }
                if (arg == "--optimize")
                {
                    optimize = true;
                }
            }
            var converter = new AptConverter();
            converter.ConvertToApt(args[0], optimize, isra3);
        }
    }
}
