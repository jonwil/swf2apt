using SwfLib.Data;
using SwfLib.Tags.TextTags;

namespace eaf2apt.Characters
{
    class AptCharacterText : AptCharacter
    {
        public DefineEditTextTag Tag;
        public AptRect BoundingRect;
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Text);
            GlobalData.output.Write(3, 0x09876543);
            GlobalData.output.Write(3, BoundingRect);
            GlobalData.output.Write(3, (int)Tag.FontID);
            GlobalData.output.Write(3, (int)Tag.Align);
            SwfRGBA color;
            if (Tag.TextColor is not null)
            {
                color = Tag.TextColor.Value;
            }
            else
            {
                color = new SwfRGBA { Red = 255, Green = 255, Blue = 255, Alpha = 255 };
            }
            GlobalData.output.Write(3, color);
            GlobalData.output.Write(3, Tag.FontHeight / 20.0f);
            GlobalData.output.Write(3, Tag.ReadOnly);
            GlobalData.output.Write(3, Tag.Multiline);
            GlobalData.output.Write(3, Tag.WordWrap);
            GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_InitialText");
            GlobalData.output.WriteFixup(3, @$"{GetHashCode()}_VariableName");
            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_InitialText");
            GlobalData.output.Write(4, Tag.InitialText);
            GlobalData.output.Align(4);
            GlobalData.output.FixupPointer(4, @$"{GetHashCode()}_VariableName");
            GlobalData.output.Write(4, Tag.VariableName);
        }
        public AptCharacterText(DefineEditTextTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            Tag = tag;
            BoundingRect = new AptRect { fLeft = tag.Bounds.XMin / 20.0f, fTop = tag.Bounds.YMin / 20.0f, fRight = tag.Bounds.XMax / 20.0f, fBottom = tag.Bounds.YMax / 20.0f };
        }
    }
}