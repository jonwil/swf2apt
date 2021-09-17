﻿using SwfLib.Tags.ControlTags;

namespace eaf2apt.Controls
{
    class AptControlFrameLabel : AptControl
    {
        public FrameLabelTag Tag;
        public AptControlFrameLabel(FrameLabelTag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            base.OutputControl(str, i);
            GlobalData.output.Write(6, (int)AptControlType.FrameLabel);
            GlobalData.output.Align(6);
            GlobalData.output.WriteFixup(6, @$"{str}_Name");
            GlobalData.output.Write(6, (ushort)0);
            GlobalData.output.Write(6, (ushort)AptVirtualFunctionTable_Indices.AptVFT_Integer);
            GlobalData.output.Write(6, i);
            GlobalData.output.Align(7);
            GlobalData.output.FixupPointer(7, @$"{str}_Name");
            GlobalData.output.Write(7, Tag.Name);
        }
    }
}
