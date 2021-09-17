using System.Collections.Generic;
using SwfLib.Shapes.FillStyles;
using SwfLib.Shapes.LineStyles;
using SwfLib.Shapes.Records;

namespace SwfLib.Tags.ShapeMorphingTags {
    public class DefineMorphShapeTag : ShapeMorphingBaseTag {
        public readonly List<LineStyleRGBA> StartLineStyles = new List<LineStyleRGBA>();
        public readonly List<LineStyleRGBA> EndLineStyles = new List<LineStyleRGBA>();
        public readonly List<FillStyleRGBA> StartFillStyles = new List<FillStyleRGBA>();
        public readonly List<FillStyleRGBA> EndFillStyles = new List<FillStyleRGBA>();
        public readonly List<IShapeRecordRGBA> StartShapeRecords = new List<IShapeRecordRGBA>();
        public readonly List<IShapeRecordRGBA> EndShapeRecords = new List<IShapeRecordRGBA>();

        public override SwfTagType TagType {
            get { return SwfTagType.DefineMorphShape; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override int TagID => CharacterID;
    }
}
