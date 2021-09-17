namespace SwfLib.Tags.SoundTags {
    public class StartSoundTag : SwfTagBase {
        public int SoundID { get; set; }
        public override SwfTagType TagType {
            get { return SwfTagType.StartSound; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override bool IsControlTag => true;
    }
}
