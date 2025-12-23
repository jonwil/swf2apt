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

using SwfLib.Tags.DisplayListTags;

namespace eaf2apt.Controls
{
    class AptControlPlaceObject2 : AptControl
    {
        public PlaceObject2Tag Tag;
        public AptControlPlaceObject2(PlaceObject2Tag tag, Globals globaldata) : base(globaldata)
        {
            Tag = tag;
        }
        public override void OutputControl(string str, int i)
        {
            {
                base.OutputControl(str, i);
                GlobalData.output.Write(6, (int)AptControlType.PlaceObject2);
                GlobalData.output.Align(6);
                GlobalData.output.Write(6, (int)Tag.Flags);
                GlobalData.output.Write(6, (int)Tag.Depth);

                if (Tag.HasCharacter)
                {
                    GlobalData.output.Write(6, (int)Tag.CharacterID);
                }
                else
                {
                    GlobalData.output.Write(6, -1);
                }

                GlobalData.output.Write(6, Tag.Matrix);
                GlobalData.output.Write(6, Tag.ColorTransform, Tag.HasColorTransform);

                if (Tag.HasRatio)
                {
                    GlobalData.output.Write(6, Tag.Ratio / 65536.0f);
                }
                else
                {
                    GlobalData.output.Write(6, (float)0);
                }

                if (Tag.HasName)
                {
                    GlobalData.output.WriteFixup(6, @$"{str}_Name");
                    GlobalData.output.Align(7);
                    GlobalData.output.FixupPointer(7, @$"{str}_Name");
                    GlobalData.output.Write(7, Tag.Name);
                }
                else
                {
                    GlobalData.output.Write(6, 0);
                }

                if (Tag.HasClipDepth)
                {
                    GlobalData.output.Write(6, (int)Tag.ClipDepth);
                }
                else
                {
                    GlobalData.output.Write(6, -1);
                }

                if (Tag.ClipActions.Records.Count > 0)
                {
                    GlobalData.output.WriteFixup(6, @$"{str}_ClipActions");
                    GlobalData.output.Align(7);
                    GlobalData.output.FixupPointer(7, @$"{str}_ClipActions");
                    GlobalData.output.Write(7, Tag.ClipActions.Records.Count);
                    GlobalData.output.WriteFixup(7, @$"{str}_EventActions");
                    GlobalData.output.Align(8);
                    GlobalData.output.FixupPointer(8, @$"{str}_EventActions");

                    foreach (var a in Tag.ClipActions.Records)
                    {
                        GlobalData.output.Write(8, a.Flags);
                        GlobalData.output.Write(8, (int)a.KeyCode);
                        GlobalData.writer.WriteActions(8, @$"{str}_{a.GetHashCode()}", a.Actions);
                    }
                }
                else
                {
                    GlobalData.output.Write(6, 0);
                }
            }
        }
    }
}
