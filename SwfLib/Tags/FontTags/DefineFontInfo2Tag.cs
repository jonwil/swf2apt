namespace SwfLib.Tags.FontTags {
    public class DefineFontInfo2Tag : DefineFontInfoBaseTag
    {

        public override SwfTagType TagType {
            get { return SwfTagType.DefineFontInfo2; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override int TagID => FontID;
    }
}
