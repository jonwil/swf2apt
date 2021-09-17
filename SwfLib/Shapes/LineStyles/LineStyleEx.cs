﻿using SwfLib.Data;
using SwfLib.Shapes.FillStyles;

namespace SwfLib.Shapes.LineStyles {
    public struct LineStyleEx : ILineStyle {

        /// <summary>
        /// Gets or sets line width.
        /// </summary>
        public ushort Width { get; set; }

        public CapStyle StartCapStyle { get; set; }

        public JoinStyle JoinStyle { get; set; }

        public bool HasFill { get; set; }

        public bool NoHScale { get; set; }

        public bool NoVScale { get; set; }

        public bool PixelHinting { get; set; }

        public byte Reserved { get; set; }

        public bool NoClose { get; set; }

        public CapStyle EndCapStyle { get; set; }

        public double MilterLimitFactor { get; set; }

        /// <summary>
        /// gets or sets line color.
        /// </summary>
        public SwfRGBA Color { get; set; }

        public FillStyleRGBA FillStyle { get; set; }
    }
}
