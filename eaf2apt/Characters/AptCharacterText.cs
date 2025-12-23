/*
**	swf2apt
**	Copyright 2025 Jonathan Wilson
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

            if (GlobalData.IsTT)
            {
                GlobalData.output.Write(3, 0x0);
                GlobalData.output.Write(3, 0x0);
            }

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
