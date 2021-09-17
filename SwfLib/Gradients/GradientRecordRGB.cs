using SwfLib.Data;
using System;
using System.Collections.Generic;

namespace SwfLib.Gradients {
    /// <summary>
    /// Represents gradient RGB record.
    /// </summary>
    public class GradientRecordRGB {

        /// <summary>
        /// Gets or sets ration.
        /// </summary>
        public byte Ratio { get; set; }

        /// <summary>
        /// Gets or sets color.
        /// </summary>
        public SwfRGB Color { get; set; }

        public override bool Equals(object obj)
        {
            return obj is GradientRecordRGB rGB &&
                   Ratio == rGB.Ratio &&
                   EqualityComparer<SwfRGB>.Default.Equals(Color, rGB.Color);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Ratio, Color);
        }
    }
}
