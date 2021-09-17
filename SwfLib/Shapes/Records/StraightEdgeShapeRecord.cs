﻿namespace SwfLib.Shapes.Records {
    public class StraightEdgeShapeRecord : IShapeRecordRGB, IShapeRecordRGBA, IShapeRecordEx {

        /// <summary>
        /// Gets or sets delta X.
        /// </summary>
        public int DeltaX { get; set; }

        /// <summary>
        /// Gets or sets the delta Y.
        /// </summary>
        public int DeltaY { get; set; }

        public ShapeRecordType Type {
            get { return ShapeRecordType.StraightEdge; }
        }

        public TResult AcceptVisitor<TArg, TResult>(IShapeRecordVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }

        public override string ToString() {
            return string.Format("Straight: delta ({0}, {1})", DeltaX, DeltaY);
        }
    }
}
