using SwfLib.Tags.VideoTags;

namespace eaf2apt.Characters
{
    class AptCharacterVideo : AptCharacter
    {
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Video);
            GlobalData.output.Write(3, 0x09876543);
        }
        public AptCharacterVideo(DefineVideoStreamTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
        }
    }
}
