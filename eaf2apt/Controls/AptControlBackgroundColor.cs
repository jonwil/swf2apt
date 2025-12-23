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
