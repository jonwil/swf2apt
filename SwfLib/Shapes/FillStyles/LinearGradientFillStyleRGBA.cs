﻿using SwfLib.Data;
using SwfLib.Gradients;

namespace SwfLib.Shapes.FillStyles {
    public class LinearGradientFillStyleRGBA : FillStyleRGBA {

        public SwfMatrix GradientMatrix = SwfMatrix.Identity;

        public GradientRGBA Gradient;

        public ushort BitmapID;

        public override FillStyleType Type {
            get { return FillStyleType.LinearGradient; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IFillStyleRGBAVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
    }
}
