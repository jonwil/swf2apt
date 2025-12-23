namespace SwfLib.Tags.SoundTags {
    public class DefineSoundTag : SwfTagBase {
        public ushort SoundID { get; set; }
        /// <summary>
        /// Gets swf tag type.
        /// </summary>
        public override SwfTagType TagType {
            get { return SwfTagType.DefineSound; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override int TagID => SoundID;
        public byte SoundFormat;
        public byte SoundRate;
        public byte SoundSize;
        public byte SoundType;
        public uint SoundSampleCount;
        public byte[] SoundData;
    }
}
