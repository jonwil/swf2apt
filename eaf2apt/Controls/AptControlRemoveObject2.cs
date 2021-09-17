using SwfLib.Tags.DisplayListTags;

namespace eaf2apt.Controls
{
    class AptControlRemoveObject2 : AptControl
    {
        public RemoveObject2Tag Tag;
        public AptControlRemoveObject2(RemoveObject2Tag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.RemoveObject2);
            GlobalData.output.Align(6);
            GlobalData.output.Write(6, (int)Tag.Depth);
        }
    }
}
