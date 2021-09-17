﻿using SwfLib.Data;
using SwfLib.Gradients;

namespace SwfLib.Shapes.FillStyles {
    public class RadialGradientFillStyleRGBA : FillStyleRGBA {

        public SwfMatrix GradientMatrix = SwfMatrix.Identity;

        public GradientRGBA Gradient;

        public ushort BitmapID;

        /// <summary>
        /// Gets type of fill style.
        /// </summary>
        public override FillStyleType Type {
            get { return FillStyleType.RadialGradient; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IFillStyleRGBAVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
    }
}
