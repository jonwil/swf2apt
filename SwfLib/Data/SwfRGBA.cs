using System;

namespace SwfLib.Data {
    /// <summary>
    /// Represents RGBA color.
    /// </summary>
    public struct SwfRGBA {

        public SwfRGBA(SwfRGB rgb)
        {
            Red = rgb.Red;
            Green = rgb.Green;
            Blue = rgb.Blue;
            Alpha = 255;
        }

        public SwfRGBA(byte red, byte green, byte blue, byte alpha) {
            Red = red;
            Green = green;
            Blue = blue;
            Alpha = alpha;
        }


        public byte Red;

        public byte Green;

        public byte Blue;

        public byte Alpha;

        public override bool Equals(object obj)
        {
            return obj is SwfRGBA rGBA &&
                   Red == rGBA.Red &&
                   Green == rGBA.Green &&
                   Blue == rGBA.Blue &&
                   Alpha == rGBA.Alpha;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Red, Green, Blue, Alpha);
        }
    }
}
