/*
**	swf2apt
**	Copyright 2025 Jonathan Wilson
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
                Console.WriteLine("Usage: eaf2apt infile outpath [--ra3|--tt]");
                Console.WriteLine();
                Console.WriteLine("infile is the name of the input swf file");
                Console.WriteLine("outpath is the path to output to");
                Console.WriteLine("pass --ra3 if you are exporting for RA3 or Uprising, --tt for Tiberian Twilight or neither for Tiberium Wars or Kane's Wrath");
                Console.WriteLine();
            }

            bool isra3 = false;

            if (args.Length >= 3 && args[2] == "--ra3")
            {
                isra3 = true;
            }

            bool istt = false;

            if (args.Length >= 3 && args[2] == "--tt")
            {
                isra3 = true;
                istt = true;
            }

            var converter = new AptConverter();
            converter.ConvertToApt(args[0], args[1], isra3, istt);
        }
    }
}
