﻿using System.Collections.Generic;
using SwfLib.Shapes.FillStyles;
using SwfLib.Shapes.LineStyles;

namespace SwfLib.Shapes.Records {
    [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "RGBA")]
    public class StyleChangeShapeRecordRGBA : StyleChangeShapeRecord, IShapeRecordRGBA {

        public readonly List<FillStyleRGBA> FillStyles = new List<FillStyleRGBA>();

        public readonly List<LineStyleRGBA> LineStyles = new List<LineStyleRGBA>();

        public override TResult AcceptVisitor<TArg, TResult>(IShapeRecordVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
    }
}
