using SwfLib.Data;

namespace SwfLib.Shapes.FillStyles
{
    public class SolidMorphFillStyleRGBA : FillStyleRGBA
    {

        public SwfRGBA StartColor { get; set; }
        public SwfRGBA EndColor { get; set; }

        /// <summary>
        /// Gets type of fill style.
        /// </summary>
        public override FillStyleType Type
        {
            get { return FillStyleType.SolidColor; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IFillStyleRGBAVisitor<TArg, TResult> visitor, TArg arg)
        {
            return visitor.Visit(this, arg);
        }
    }
}
