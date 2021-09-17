using SwfLib.Tags.ActionsTags;

namespace eaf2apt.Controls
{
    class AptControlDoInitAction : AptControl
    {
        public DoInitActionTag Tag;
        public AptControlDoInitAction(DoInitActionTag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.DoInitAction);
            GlobalData.output.Align(6);
            GlobalData.output.Write(6, (int)Tag.SpriteId);
            GlobalData.writer.WriteActions(6, @$"{str}_actions", Tag.ActionRecords);
        }
    }
}
