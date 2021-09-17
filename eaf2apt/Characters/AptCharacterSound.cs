using SwfLib.Tags.SoundTags;

namespace eaf2apt.Characters
{
    class AptCharacterSound : AptCharacter
    {
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Sound);
            GlobalData.output.Write(3, 0x09876543);
            GlobalData.output.Write(3, i);
        }
        public AptCharacterSound(DefineSoundTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
        }
    }
}