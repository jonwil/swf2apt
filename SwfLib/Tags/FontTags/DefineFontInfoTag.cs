namespace SwfLib.Tags.FontTags {
    public class DefineFontInfoTag : DefineFontInfoBaseTag {

        public override SwfTagType TagType {
            get { return SwfTagType.DefineFontInfo; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override int TagID => FontID;
    }
}
