﻿using SwfLib.Data;

namespace SwfLib.Shapes.FillStyles {
    public class SolidFillStyleRGBA : FillStyleRGBA {

        public SwfRGBA Color { get; set; }

        /// <summary>
        /// Gets type of fill style.
        /// </summary>
        public override FillStyleType Type {
            get { return FillStyleType.SolidColor; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IFillStyleRGBAVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
    }
}
