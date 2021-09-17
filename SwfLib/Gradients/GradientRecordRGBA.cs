using SwfLib.Data;
using System;
using System.Collections.Generic;

namespace SwfLib.Gradients {
    public class GradientRecordRGBA {

        public byte Ratio;

        public SwfRGBA Color;

        public override bool Equals(object obj)
        {
            return obj is GradientRecordRGBA rGBA &&
                   Ratio == rGBA.Ratio &&
                   EqualityComparer<SwfRGBA>.Default.Equals(Color, rGBA.Color);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Ratio, Color);
        }
    }
}
