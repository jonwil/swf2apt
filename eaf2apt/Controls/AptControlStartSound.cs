using SwfLib.Tags.SoundTags;

namespace eaf2apt.Controls
{
    class AptControlStartSound : AptControl
    {
        public StartSoundTag Tag;
        public AptControlStartSound(StartSoundTag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.StartSound);
            GlobalData.output.Align(6);
            GlobalData.output.Write(6, Tag.SoundID);
        }
    }
}