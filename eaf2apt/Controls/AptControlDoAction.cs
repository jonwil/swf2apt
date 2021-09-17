using SwfLib.Tags.ActionsTags;

namespace eaf2apt.Controls
{
    class AptControlDoAction : AptControl
    {
        public DoActionTag Tag;
        public AptControlDoAction(DoActionTag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.DoAction);
            GlobalData.output.Align(6);
            GlobalData.writer.WriteActions(6, @$"{str}_actions", Tag.ActionRecords);
        }
    }
}