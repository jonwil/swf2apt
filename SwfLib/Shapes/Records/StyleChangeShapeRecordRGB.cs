﻿using System.Collections.Generic;
using SwfLib.Shapes.FillStyles;
using SwfLib.Shapes.LineStyles;

namespace SwfLib.Shapes.Records {
    public class StyleChangeShapeRecordRGB : StyleChangeShapeRecord, IShapeRecordRGB {

        public readonly List<FillStyleRGB> FillStyles = new List<FillStyleRGB>();

        public readonly List<LineStyleRGB> LineStyles = new List<LineStyleRGB>();

        public override TResult AcceptVisitor<TArg, TResult>(IShapeRecordVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
    }
}
