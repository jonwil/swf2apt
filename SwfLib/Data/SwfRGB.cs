using System;
using System.Diagnostics;

namespace SwfLib.Data {
    [DebuggerDisplay("Red: {Red}, Green: {Green}, Blue:  {Blue}")]
    public struct SwfRGB {

        public SwfRGB(byte red, byte green, byte blue) {
            Red = red;
            Green = green;
            Blue = blue;
        }


        public byte Red;

        public byte Green;

        public byte Blue;

        public override bool Equals(object obj)
        {
            return obj is SwfRGB rGB &&
                   Red == rGB.Red &&
                   Green == rGB.Green &&
                   Blue == rGB.Blue;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Red, Green, Blue);
        }
    }
}