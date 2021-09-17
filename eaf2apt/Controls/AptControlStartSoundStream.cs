using SwfLib.Tags.SoundTags;

namespace eaf2apt.Controls
{
    class AptControlStartSoundStream : AptControl
    {
        public SoundStreamHeadTag Tag;
        public int ID;
        public AptControlStartSoundStream(SoundStreamHeadTag tag, int id, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
            ID = id;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.StartSoundStream);
            GlobalData.output.Align(6);
            GlobalData.output.Write(6, ID);
        }
    }
}
