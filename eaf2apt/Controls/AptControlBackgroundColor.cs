using SwfLib.Tags.ControlTags;

namespace eaf2apt.Controls
{
    class AptControlBackgroundColor : AptControl
    {
        public SetBackgroundColorTag Tag;
        public AptControlBackgroundColor(SetBackgroundColorTag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }

        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.BackgroundColour);
            GlobalData.output.Align(6);
            GlobalData.output.Write(6, Tag.Color);
        }
    }
}
